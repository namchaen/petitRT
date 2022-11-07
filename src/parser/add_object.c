#include "parser.h"
#include "object.h" // t_object -> t_light 하면 지울 수 있음
#include "scene.h"

void	add_light(t_parse_info *info, int i, char *line, t_object **light_obj)
{
	t_light	*light;

	if (info->single_light != FALSE)
		parse_error("redefinition of lighting", i);
	info->single_light = TRUE;
	if (line_scanf(i, line, LSCANF_L, &info->p.x, &info->p.y, &info->p.z
		, &info->ratio, &info->c.x, &info->c.y, &info->c.z) != 7)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| info->ratio < EPSILON)
		parse_error("out of range", i);
	light = light_new(&info->p, &info->c, info->ratio);
	printf("L line [%02d]: p(%f,%f,%f) r:%f c(%f,%f,%f) \n", i, info->p.x, info->p.y, info->p.z
		, info->ratio, info->c.x, info->c.y, info->c.z);
	info->c = vec3(0, 0, 0); // t_object -> t_light 하면 지울 수 있음
	oadd(light_obj, object_new(LIGHT, light, &info->c));
}

void	add_camera(t_parse_info *info, int i, char *line, t_camera **cam)
{
	if (info->single_camera != FALSE)
		parse_error("redefinition of camera", i);
	info->single_camera = TRUE;
	if (line_scanf(i, line, LSCANF_C, &info->p.x, &info->p.y, &info->p.z
		,&info->n.x, &info->n.y, &info->n.z, &info->fov) != 7)
		parse_error("unmatched number", i);
	if (is_vec_in_range(&info->n, -1, 1) == FALSE
		|| info->fov < 0 || info->fov > 180)
		parse_error("out of range", i);
	*cam = camera_new(info->p, info->n, info->fov);
	printf("C line [%02d]: p(%f,%f,%f) n(%f,%f,%f) fov:%f\n", i, info->p.x, info->p.y, info->p.z
		, info->n.x, info->n.y, info->n.z, info->fov);
}
