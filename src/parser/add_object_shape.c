/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object_shape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:09:55 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/15 05:07:35 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "object.h"

void	add_plane(t_parse_info *info, int i, char *line, t_scene *scene)
{
	t_plane	*pl;

	if (line_scanf(i, line, LSCANF_PL, &info->p.x, &info->p.y, &info->p.z,
			&info->n.x, &info->n.y, &info->n.z,
			&info->c.x, &info->c.y, &info->c.z) != 9)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| is_vec_in_range(&info->n, -1, 1) == FALSE)
		parse_error("out of range", i);
	pl = plane_new(&info->p, &info->n);
	info->c = vmul(info->c, RGB_NORMAL);
	oadd(&scene->object, object_new(PL, pl, &info->c));
	printf("pl line [%02d]: p(%f,%f,%f) n(%f,%f,%f) c(%f,%f,%f)\n", i, info->p.x, info->p.y, info->p.z
		, info->n.x, info->n.y, info->n.z, info->c.x, info->c.y, info->c.z);
}

void	add_sphere(t_parse_info *info, int i, char *line, t_scene *scene)
{
	t_sphere	*sp;

	if (line_scanf(i, line, LSCANF_SP, &info->p.x, &info->p.y, &info->p.z,
			&info->diameter, &info->c.x, &info->c.y, &info->c.z) != 7)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| info->diameter / 2.0 <= 0)
		parse_error("out of range", i);
	sp = sphere_new(&info->p, info->diameter / 2.0);
	info->c = vmul(info->c, RGB_NORMAL);
	oadd(&scene->object, object_new(SP, sp, &info->c));
	printf("sp line [%02d]: p(%f,%f,%f) diameter:%f c(%f,%f,%f)\n", i, info->p.x, info->p.y, info->p.z
		, info->diameter, info->c.x, info->c.y, info->c.z);
}

void	add_cylinder(t_parse_info *info, int i, char *line, t_scene *scene)
{
	t_cylinder	*cy;

	if (line_scanf(i, line, LSCANF_CY, &info->p.x, &info->p.y, &info->p.z
			, &info->n.x, &info->n.y, &info->n.z
			, &info->diameter, &info->height
			, &info->c.x, &info->c.y, &info->c.z) != 11)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| is_vec_in_range(&info->n, -1, 1) == FALSE
		|| info->diameter / 2.0 <= 0
		|| info->height <= 0)
		parse_error("out of range", i);
	cy = cylinder_new(&info->p, &info->n, info->diameter / 2.0, info->height);
	info->c = vmul(info->c, RGB_NORMAL);
	oadd(&scene->object, object_new(CY, cy, &info->c));
	printf("cy line [%02d]: p(%f,%f,%f) n(%f,%f,%f) d:%f h:%f c(%f,%f,%f)\n", i, info->p.x, info->p.y, info->p.z
		, info->n.x, info->n.y, info->n.z, info->diameter, info->height
		,info->c.x, info->c.y, info->c.z);
}
