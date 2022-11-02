#include "ray.h"
#include <math.h>

static t_bool	check_root(t_cylinder *cy, t_ray *ray, t_hit_record *rec, float root)
{
	t_point3	p;
	t_vec3		pc[2];

	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	p = ray_at(ray, root);
	pc[0] = vsub_(p, cy->center_base);
	pc[1] = vsub_(p, cy->center_top);
	if (vdot(pc[0], cy->h) < 0 || vdot(pc[1], cy->h) > cy->height)
		return (FALSE);
	return (TRUE);
}

static t_bool	is_hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec, float *root)
{
	if (check_root(cy, ray, rec, root[0]))
		return (TRUE);
	if (check_root(cy, ray, rec, root[1]))
	{
		root[0] = root[1];
		return (TRUE);
	}
	return (FALSE);
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
	float		root[2];

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
	root[0] = (-half_b - sqrtd) / a;
	root[1] = (-half_b + sqrtd) / a;
	if (is_hit_cylinder(cy, ray, rec, root) == FALSE)
		return (FALSE);
	rec->t = root[0];
	rec->p = ray_at(ray, rec->t);
	rec->normal = vunit(vsub_(rec->p, cy->center));
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}
