#include "ray.h"
#include <math.h>

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_vec3		oc;
	float		a;
	float		half_b;
	float		c;
	float		discriminant;
	float		sqrtd;
	float		root;

	sp = sp_obj->element;
	oc = vsub_(ray->orig, sp->center);
	a = vnorm2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vnorm2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdiv(vsub_(rec->p, sp->center), sp->radius);
	rec->albedo = sp_obj->albedo;
	record_set_face_normal(ray, rec);
	return (TRUE);
}