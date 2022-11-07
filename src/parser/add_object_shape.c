#include "parser.h"
#include "object.h"

void	add_plane(t_parse_info *info, int i, char *line, t_object **obj)
{
	t_plane *pl;

	if (line_scanf(i, line, LSCANF_PL, &info->p.x, &info->p.y, &info->p.z
		, &info->n.x, &info->n.y, &info->n.z
		, &info->c.x, &info->c.y, &info->c.z) != 9)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| is_vec_in_range(&info->n, -1, 1) == FALSE)
		parse_error("out of range", i);
	pl = plane_new(&info->p, &info->n);
	oadd(obj, object_new(PL, pl, &info->c));
	printf("pl line [%02d]: p(%f,%f,%f) n(%f,%f,%f) c(%f,%f,%f)\n", i, info->p.x, info->p.y, info->p.z
		, info->n.x, info->n.y, info->n.z, info->c.x, info->c.y, info->c.z);
}

void	add_sphere(t_parse_info *info, int i, char *line, t_object **obj)
{
	t_sphere *sp;

	if (line_scanf(i, line, LSCANF_SP, &info->p.x, &info->p.y, &info->p.z
		, &info->diameter, &info->c.x, &info->c.y, &info->c.z) != 7)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| info->diameter / 2.0 <= EPSILON)
		parse_error("out of range", i);
	sp = sphere_new(&info->p, info->diameter / 2.0);
	oadd(obj, object_new(SP, sp, &info->c));
	printf("sp line [%02d]: p(%f,%f,%f) diameter:%f c(%f,%f,%f)\n", i, info->p.x, info->p.y, info->p.z
		, info->diameter, info->c.x, info->c.y, info->c.z);
}

void	add_cylinder(t_parse_info *info, int i, char *line, t_object **obj)
{
	t_cylinder *cy;

	printf("cy!!!!!!!!\n");
	if (line_scanf(i, line, LSCANF_CY, &info->p.x, &info->p.y, &info->p.z
		, &info->n.x, &info->n.y, &info->n.z
		, &info->diameter, &info->height
		, &info->c.x, &info->c.y, &info->c.z) != 11)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| is_vec_in_range(&info->n, -1, 1) == FALSE
		|| info->diameter / 2.0 <= EPSILON
		|| info->height <= EPSILON)
		parse_error("out of range", i);
	cy = cylinder_new(&info->p, &info->n, info->diameter / 2.0, info->height);
	oadd(obj, object_new(CY, cy, &info->c));
	printf("cy line [%02d]: p(%f,%f,%f) n(%f,%f,%f) d:%f h:%f c(%f,%f,%f)\n", i, info->p.x, info->p.y, info->p.z
		, info->n.x, info->n.y, info->n.z, info->diameter, info->height
		,info->c.x, info->c.y, info->c.z);
}
