#include "ray.h"

static t_bool	set_eqaution(t_eqtn *eqtn, t_cylinder *cy,
					t_ray *ray, t_hit_record *rec);
static t_bool	is_hit_cylinder(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, t_eqtn *eqtn);
static t_bool	check_base_cap(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, float *root);
static t_bool	check_top_cap(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, float *root);

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_eqtn		eqtn;

	cy = cy_obj->element;
	if (set_eqaution(&eqtn, cy, ray, rec) == FALSE)
		return (FALSE);
	if (is_hit_cylinder(cy, ray, rec, &eqtn) == FALSE)
		return (FALSE);
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}

//일단 두 근을 구한다
static t_bool	set_eqaution(t_eqtn *eqtn, t_cylinder *cy,
					t_ray *ray, t_hit_record *rec)
{
	t_vec3	oc;
	t_vec3	v;
	float	v_dot_n;
	float	w_dot_h;

	(void)rec;
	v = ray->dir;
	oc = vsub_(ray->orig, cy->center_base);
	v_dot_n = vdot(v, cy->normal);
	w_dot_h = vdot(oc, cy->normal);
	eqtn->a = vnorm2(v) - v_dot_n * v_dot_n;
	eqtn->half_b = vdot(v, oc) - v_dot_n * w_dot_h;
	eqtn->c = vnorm2(oc) - w_dot_h * w_dot_h - cy->radius2;
	eqtn->discriminant = eqtn->half_b * eqtn->half_b - eqtn->a * eqtn->c;
	if (eqtn->a == 0 || eqtn->discriminant <= 0)
		return (FALSE);
	eqtn->sqrtd = sqrt(eqtn->discriminant);
	eqtn->root = (-eqtn->half_b - eqtn->sqrtd) / eqtn->a;
	eqtn->root1 = (-eqtn->half_b + eqtn->sqrtd) / eqtn->a;
	//if (eqtn->root < rec->tmin || rec->tmax < eqtn->root)
	//{
	//	eqtn->root = (-eqtn->half_b + eqtn->sqrtd) / eqtn->a;
	//	if (eqtn->root < rec->tmin || rec->tmax < eqtn->root)
	//		return (FALSE);
	//}
	eqtn->root_modified = FALSE;
	return (TRUE);
}

//
static t_bool	is_hit_cylinder(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, t_eqtn *eqtn)
{
	t_point3	p[2];
	t_vec3		pc[2];
	float		height[2];
	t_cap_hit	cap_hit[2];

	//두 근에 의한 각각의 p
	p[0] = ray_at(ray, eqtn->root);
	p[1] = ray_at(ray, eqtn->root1);

	//두 근과 기준점을 뺀 벡터
	pc[0] = vsub_(p[0], cy->center_base);
	pc[1] = vsub_(p[1], cy->center_base);
	//벡터에서 노멀벡터를 곱해서 구한 height
	height[0] = vdot(pc[0], cy->normal);
	height[1] = vdot(pc[1], cy->normal);
	//cap에 맞는지 안 맞는지
	cap_hit[0] = NONE;
	cap_hit[1] = NONE;
	if (height[0] < 0)
	{
		//첫번째 hit root를 통한 base체크
		if (check_base_cap(cy, ray, rec, &eqtn->root))
			cap_hit[0] = BASE;
		else
			return (FALSE);
	}
	else if (height[0] > cy->height)
	{
		//첫번째 hit root를 통한 top체크
		if (check_top_cap(cy, ray, rec, &eqtn->root))
			cap_hit[0] = TOP;
		else
			return (FALSE);
	}
	//어딘가에 맞았으면--root값으로 if어딘가에 안 맞았으면 아래로 빠진다.
	if (cap_hit[0] != NONE)
	{
		//root가 유효근이 아니라면 return (FALSE).... 하지만 eqtn->root1이 유효근이라면?
		if (eqtn->root < rec->tmin || rec->tmax < eqtn->root)
			return (FALSE);
		//이하 root가 유효근 후보라면, rec->t, rec-> normal, rec->p을 넣어주고 return....
		rec->t = eqtn->root;
		if (cap_hit[0] == BASE)
			rec->normal = vmul(cy->normal, -1);
		else
			rec->normal = cy->normal;
		rec->p = ray_at(ray, rec->t);
		return (TRUE);
	}
	//
	if (height[1] < 0)
	{
		//
		if (check_base_cap(cy, ray, rec, &eqtn->root1))
			cap_hit[1] = BASE;
		else
			return (FALSE);
	}
	//
	else if (height[1] > cy->height)
	{
		if (check_top_cap(cy, ray, rec, &eqtn->root1))
			cap_hit[1] = TOP;
		else
			return (FALSE);
	}
	//만약에 root1이 유효한 근이라면...! && root1로 구한 height로 cap이나 bottom중 어느 한 곳에 맞았다면
	if (cap_hit[1] !=0 NONE)
	{
		if (eqtn->root1 < rec->tmin || rec->tmax < eqtn->root1)
			return (FALSE);
		rec->t = eqtn->root1;
		if (cap_hit[1] == BASE)
			rec->normal = vmul(cy->normal, -1);
		else
			rec->normal = cy->normal;
		rec->p = ray_at(ray, rec->t);
		//return (TRUE);
	}
	if (eqtn->root < rec->tmin || rec->tmax < eqtn->root)
	{
		eqtn->root = eqtn->root1;
		height[0] = height[1];
		if (eqtn->root < rec->tmin || rec->tmax < eqtn->root)
			return (FALSE);
	}
	rec->t = eqtn->root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = vunit(vsub_(rec->p,
				vadd_(cy->center_base, vmul(cy->normal, height[0]))));
	return (TRUE);
}

static t_bool	check_base_cap(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, float *root)
{
	float	dn;
	float	t;
	t_vec3	pc;

	dn = vdot(ray->dir, cy->normal);
	if (fabs(dn) <= EPSILON)
		return (FALSE);
	t = vdot(vsub_(cy->center_base, ray->orig), cy->normal) / dn;
	if (t < rec->tmin || rec->tmax < t)
		return (FALSE);
	pc = vsub_(ray_at(ray, t), cy->center_base);
	if (fabs(vdot(pc, cy->normal)) > EPSILON || vnorm(pc) > cy->radius)
		return (FALSE);
	*root = t;
	//eqtn->root = t;
	//eqtn->root_modified = TRUE;
	//rec->t = eqtn->root;
	//rec->p = ray_at(ray, rec->t);
	//rec->normal = vmul(cy->normal, -1);
	return (TRUE);
}

static t_bool	check_top_cap(t_cylinder *cy, t_ray *ray,
					t_hit_record *rec, float *root)
{
	float	dn;
	float	t;
	t_vec3	pc;

	dn = vdot(ray->dir, cy->normal);
	if (fabs(dn) <= EPSILON)
		return (FALSE);
	t = vdot(vsub_(cy->center_top, ray->orig), cy->normal) / dn;
	if (t < rec->tmin || rec->tmax < t)
		return (FALSE);
	pc = vsub_(ray_at(ray, t), cy->center_top);
	if (fabs(vdot(pc, cy->normal)) > EPSILON || vnorm(pc) > cy->radius)
		return (FALSE);
	*root = t;
	//eqtn->root = t;
	//eqtn->root_modified = TRUE;
	//rec->t = eqtn->root;
	//rec->p = ray_at(ray, rec->t);
	//rec->normal = cy->normal;
	return (TRUE);
}
