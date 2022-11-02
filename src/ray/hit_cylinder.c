#include "ray.h"
#include <math.h>

float		root[2];
t_vec3		rb[2];
t_vec3		rt[2];
float		rb_[2];
float		rt_[2];

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_vec3		oc;
	t_vec3		hc_unit;
	float		v_dot_n;
	float		w_dot_h;
	float		a;
	float		half_b;
	float		c;
	float		discriminant;
	float		sqrtd;

	// w = oc;
	// v = ray->dir;
	// h = cy->h
	v_dot_n = vdot(ray->dir, cy->normal);
	w_dot_h = vdot(oc, cy->normal);
	cy = cy_obj->element;
	oc = vsub_(ray->orig, cy->center_base);
	a = vnorm2(ray->dir) - v_dot_n * v_dot_n;
	half_b = vdot(ray->dir, oc) - v_dot_n * w_dot_h;
	c = vnorm2(oc) - w_dot_h * w_dot_h - cy->radius2;
	discriminant = half_b * half_b - a * c;
	if (fabs(a) <= EPSILON || discriminant <= 0)
		return (FALSE);
	//if (discriminant == 0 && (vdot(ray->dir, cy->h) > 0.99 && vdot(ray->dir, cy->h) < 1.01))
	//	return (FALSE);
	sqrtd = sqrt(discriminant);
	root[0] = (-half_b - sqrtd) / a;
	root[1] = (-half_b + sqrtd) / a;
	if (vdot(oc, cy->h) < 0 || vdot(oc, cy->h) > cy->height)
	{
		rb[0] = vsub_(ray_at(ray, root[0]), cy->center_base);
		rb[1] = vsub_(ray_at(ray, root[1]), cy->center_base);
		rt[0] = vsub_(ray_at(ray, root[0]), cy->center_top);
		rt[1] = vsub_(ray_at(ray, root[1]), cy->center_top);
		if (fabs(vdot(rb[0], cy->normal)) > EPSILON && fabs(vdot(rt[0], cy->normal)) > EPSILON
			&& fabs(vdot(rb[1], cy->normal)) > EPSILON && fabs(vdot(rt[1], cy->normal)) > EPSILON)
				return (FALSE);
		//if (fabs(vdot(rb[0], cy->normal)) > EPSILON && fabs(vdot(rt[0], cy->normal)) > EPSILON)
		//{
		//	rt_[0] = pow(vnorm(rt[0]), 2);
		//	rt_[1] = pow(vnorm(rt[1]), 2);
		//	if (rt_[0] > cy->radius && rt_[1] > cy->radius)
		//		return (FALSE);
		//}
		//if (fabs(vdot(rb[1], cy->normal)) > EPSILON && fabs(vdot(rt[1], cy->normal)) > EPSILON)		
		//{
		//	rb_[0] = pow(vnorm(rb[0]), 2);
		//	rb_[1] = pow(vnorm(rb[1]), 2);
		//	if (rb_[0] > cy->radius && rb_[1] > cy->radius)
		//		return (FALSE);
		//}
		rt_[0] = pow(vnorm(rt[0]), 2);
		rt_[1] = pow(vnorm(rt[1]), 2);
		rb_[0] = pow(vnorm(rb[0]), 2);
		rb_[1] = pow(vnorm(rb[1]), 2);
		if (rt_[0] > cy->radius && rt_[1] > cy->radius && rb_[0] > cy->radius && rb_[1] > cy->radius)
			return (FALSE);
	}
	//if (vdot(oc, cy->h) < -vnorm(cy->h) || vdot(oc, cy->h) > vnorm(cy->h))
	//{
	//	root[0] = (-half_b - sqrtd) / a;
	//	root[1] = (-half_b + sqrtd) / a;
	//	rc_[0] = vnorm(vsub_(ray_at(ray, root[0]), cy->center_base));
	//	rc_[0] *= rc_[0];
	//	rc_[1] = vnorm(vsub_(ray_at(ray, root[1]), cy->center_base));
	//	rc_[1] *= rc_[1];
	//	if (rc_[0] > cy->radius2 || rc_[1] > cy->radius2)
	//		return (FALSE);
	//}
	if (root[0] < rec->tmin || rec->tmax < root[0])
	{
		if (root[1] < rec->tmin || rec->tmax < root[1])
			return (FALSE);
	}
	rec->t = root[1];
	rec->p = ray_at(ray, rec->t);
	rec->normal = cy->normal;
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}
