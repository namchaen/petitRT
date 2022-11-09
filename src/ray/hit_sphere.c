#include "ray.h"
#include <math.h>

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	t_vec3		oc;
	t_eqtn		eq;

	sp = sp_obj->element;
	oc = vsub_(ray->orig, sp->center);
	eq.a = vnorm2(ray->dir);
	eq.half_b = vdot(oc, ray->dir);
	eq.c = vnorm2(oc) - sp->radius2;
	eq.discriminant = eq.half_b * eq.half_b - eq.a * eq.c;
	if (eq.discriminant < 0)
		return (FALSE);
	eq.sqrtd = sqrt(eq.discriminant);
	eq.root = (-eq.half_b - eq.sqrtd) / eq.a;
	if (eq.root < rec->tmin || rec->tmax < eq.root)
	{
		eq.root = (-eq.half_b + eq.sqrtd) / eq.a;
		if (eq.root < rec->tmin || rec->tmax < eq.root)
			return (FALSE);
	}
	rec->t = eq.root;
	rec->p = ray_at(ray, eq.root);
	rec->normal = vdiv(vsub_(rec->p, sp->center), sp->radius);
	rec->albedo = sp_obj->albedo;
	record_set_face_normal(ray, rec);
	return (TRUE);
}