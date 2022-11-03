#include "ray.h"

t_bool	hit(t_object *object, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec; // 필요 없을 시 지우기

	temp_rec = *rec;
	hit_anything = FALSE;
	while(object)
	{
		if (hit_obj(object, ray, &temp_rec))
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		object = object->next;
	}
	return (hit_anything);
}

t_bool	hit_obj(t_object *object, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (object->type == SP)
		hit_result = hit_sphere(object, ray, rec);
	else if (object->type == PL)
		hit_result = hit_plane(object, ray, rec);
	else if (object->type == CY)
		hit_result = hit_cylinder(object, ray, rec);
	return (hit_result);
}
