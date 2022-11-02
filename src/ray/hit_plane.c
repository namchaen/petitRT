#include "ray.h"
#include <math.h>

t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	float	dn;
	float	t;

	pl = pl_obj->element;
	dn = vdot(ray->dir, pl->normal);
	if (fabs(dn) <= EPSILON)
		return (FALSE);
	t = vdot(vsub_(pl->point, ray->orig), pl->normal) / dn;
	if (t < rec->tmin || rec->tmax < t)
		return (FALSE);
	rec->t = t;
	rec->p = ray_at(ray, rec->t);
	rec->normal = pl->normal;
	rec->albedo = pl_obj->albedo;
	return (rec->t > -EPSILON);
}
