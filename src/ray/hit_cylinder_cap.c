#include "ray.h"
#include <math.h>

static t_bool	check_base_cap(t_cylinder *cy, t_hit_record *rec, t_ray *ray, float *root)
{
	float	dn;
	float	t;
	t_vec3	pc;

	// pl->normal = normal or vmul(normal, -1)
	// pl->point = center top or bottom
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
	printf("base cap\n");
	return (TRUE);
}

static t_bool	check_top_cap(t_cylinder *cy, t_ray *ray, t_hit_record *rec, float *root)
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
	printf("top cap\n");
	return (TRUE);
}

static t_bool	is_hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec, float *root)
{
	t_point3	p;
	t_vec3		pc[2];

	p = ray_at(ray, *root);
	pc[0] = vsub_(p, cy->center_base);
	pc[1] = vsub_(p, cy->center_top);
	if ( fabs(vdot(pc[1], cy->normal)) > EPSILON)

	if (vdot(pc[0], cy->h) < 0)
	{
		return (check_base_cap(cy, ray, rec, root));
	}
	if (vdot(pc[1], cy->h) > cy->height)
	{
		return (check_top_cap(cy, ray, rec, root));
	}
	return (TRUE);
}


t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_vec3		oc;
	t_vec3		v;
	float		v_dot_n;
	float		w_dot_h;
	float		a;
	float		half_b;
	float		c;
	float		discriminant;
	float		sqrtd;
	float		root;

	// w = oc;
	// v = vunit(ray->dir);
	// h = cy->h
	cy = cy_obj->element;
	v = ray->dir;	// v = vunit(ray->dir);
	oc = vsub_(ray->orig, cy->center_base);
	v_dot_n = vdot(v, cy->normal);
	w_dot_h = vdot(oc, cy->normal);
	a = vnorm2(v) - v_dot_n * v_dot_n;
	half_b = vdot(v, oc) - v_dot_n * w_dot_h;
	c = vnorm2(oc) - w_dot_h * w_dot_h - cy->radius2;
	discriminant = half_b * half_b - a * c;
	if (fabs(a) <= EPSILON || discriminant <= 0)
		return (FALSE);
	//if (discriminant == 0 && (vdot(v, cy->h) > 0.99 && vdot(v, cy->h) < 1.01))
	//	return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	if (is_hit_cylinder(cy, ray, rec, &root) == FALSE)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = vunit(vsub_(rec->p, cy->center));
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}
