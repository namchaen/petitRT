/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:10:00 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/11 19:51:43 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "object.h"
#include "scene.h"

void	add_light(t_parse_info *info, int i, char *line, t_scene *scene)
{
	t_light	*light;

	if (info->single_light != FALSE || scene->light)
		parse_error("redefinition of lighting", i);
	info->single_light = TRUE;
	if (line_scanf(i, line, LSCANF_L, &info->p.x, &info->p.y, &info->p.z
			, &info->ratio, &info->c.x, &info->c.y, &info->c.z) != 7)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| info->ratio < EPSILON)
		parse_error("out of range", i);
	info->c = vmul(info->c, RGB_NORMAL);
	light = light_new(&info->p, &info->c, info->ratio);
	info->c = vec3(0, 0, 0);
	oadd(&scene->light, object_new(LIGHT, light, &info->c));
}

void	add_camera(t_parse_info *info, int i, char *line, t_scene *scene)
{
	if (info->single_camera != FALSE || scene->camera)
		parse_error("redefinition of camera", i);
	info->single_camera = TRUE;
	if (line_scanf(i, line, LSCANF_C, &info->p.x, &info->p.y, &info->p.z
			, &info->n.x, &info->n.y, &info->n.z, &info->fov) != 7)
		parse_error("unmatched number", i);
	if (is_vec_in_range(&info->n, -1, 1) == FALSE
		|| info->fov < 0 || info->fov > 180)
		parse_error("out of range", i);
	scene->camera = camera_new(info->p, info->n, info->fov);
}
