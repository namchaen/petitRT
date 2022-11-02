#include "ray.h"
#include <math.h>

statidc void	set_discriminant(t_cylinder	*cy, float *a, float *half_b, float *c)
{
	t_vec3		oc;
	t_vec3		hc_unit;
	float		name_undefined_1;
	float		name_undefined_2;

	// w = oc;
	// v = ray->dir;
	// h = cy->vori
	name_undefined_1 = vdot(ray->dir, cy->normal);
	name_undefined_2 = vdot(oc, cy->normal);
	cy = cy_obj->element;
	oc = vsub_(ray->orig, cy->center_base);
	*a = vnorm2(ray->dir) - name_undefined_1 * name_undefined_1;
	*half_b = vdot(ray->dir, oc) - name_undefined_1 * name_undefined_2;
	*c = vnorm2(oc) - name_undefined_2 * name_undefined_2 - cy->radius2;
}

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	float		a;
	float		half_b;
	float		c;
	float		discriminant;
	float		sqrtd;
	float		root[2];
	//float		rc_[2];

	set_discriminant(cy, &a, &half_b, &c);
	discriminant = half_b * half_b - a * c;
	if (fabs(a) <= EPSILON || discriminant < 0)
		return (FALSE);
	//if (discriminant == 0 && (vdot(ray->dir, cy->vori) > 0.99 && vdot(ray->dir, cy->vori) < 1.01))
	//	return (FALSE);
	//if ()
	sqrtd = sqrt(discriminant);
	root[0] = (-half_b - sqrtd) / a;
	if (root[0] < rec->tmin || rec->tmax < root[0])
	{
		root[0] = (-half_b + sqrtd) / a;
		if (root[0] < rec->tmin || rec->tmax < root[0])
			return (FALSE);
	}
	rec->t = root[0];
	rec->p = ray_at(ray, rec->t);
	//rec->normal = // cy->normal;
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}
