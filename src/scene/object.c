#include "object.h"
#include <stdlib.h>

t_object	*create_object(t_object_type type, void *element, t_color3 albedo)
{
	t_object	*new;

	if (!(new = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = albedo;
	//new->object_handler = 
	return (new);
}

t_light	*create_light(t_point3 light_origin, t_color3 light_color, float bright_ratio)
{
	t_light	*light;

	if(!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->orig = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

t_sphere	*create_sphere(t_point3 center, float radius)
{
	t_sphere *sp;

	if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_plane	*create_plane(t_point3 point, t_vec3 normal)
{
	t_plane	*pl;

	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->point = point;
	pl->normal = vdiv(normal, vnorm(normal));
	return (pl);
}

t_cylinder	*create_cylinder(t_point3 point, t_vec3 normal, float diameter, float height)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->center_base = point;
	//cy->normal = normal;
	//cy->h = vmul(normal, height);
	cy->normal = vdiv(normal, vnorm(normal));
	cy->h = vmul(cy->normal, height);
	cy->center = vadd_(point, vdiv(cy->h, 2.0));
	cy->center_top = vadd_(point, cy->h);
	cy->radius = diameter / 2.0;
	cy->radius2 = cy->radius * cy->radius;
	cy->height = height;
	return (cy);
}