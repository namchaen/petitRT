/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:10:00 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/16 20:33:03 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "object.h"
#include "scene.h"

void	add_light(t_parse_info *info, int i, char *line, t_scene *scene)
{
	t_light		*light;
	t_color3	color;

	if (info->single_light != FALSE || scene->light)
		parse_error("redefinition of lighting", i);
	info->single_light = TRUE;
	if (line_scanf(i, line, LSCANF_L, &info->p.x, &info->p.y, &info->p.z
			, &info->ratio, &info->c.x, &info->c.y, &info->c.z) != 7)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| info->ratio < 0 || info->ratio > 1
		|| is_point_in_range(&info->p) == FALSE)
		parse_error("out of range", i);
	color = vmul(info->c, RGB_NORMAL);
	light = light_new(&info->p, &color, info->ratio);
	color = vec3(0, 0, 0);
	oadd(&scene->light, object_new(LIGHT, light, &color));
	printf("[%02d, SL]: p(%.2f,%.2f,%.2f) (%.2f) c(%.f,%.f,%.f) \n",
		i, info->p.x, info->p.y, info->p.z, info->ratio,
		info->c.x, info->c.y, info->c.z);
}

void	add_camera(t_parse_info *info, int i, char *line, t_scene *scene)
{
	t_color3	color;

	if (info->single_camera != FALSE || scene->camera)
		parse_error("redefinition of camera", i);
	info->single_camera = TRUE;
	if (line_scanf(i, line, LSCANF_C, &info->p.x, &info->p.y, &info->p.z
			, &info->n.x, &info->n.y, &info->n.z, &info->fov) != 7)
		parse_error("unmatched number", i);
	if (is_vec_in_range(&info->n, -1, 1) == FALSE
		|| info->fov < 0 || info->fov > 180
		|| is_point_in_range(&info->p) == FALSE)
		parse_error("out of range", i);
	scene->camera = camera_new(info->p, info->n, info->fov);
	color = vec3(0, 0, 0);
	oadd(&scene->cameras, object_new(CAMERA, scene->camera, &color));
	printf("[%02d, CM]: p(%.2f,%.2f,%.2f) n(%.2f,%.2f,%.2f) fov:%.2f\n",
		i, info->p.x, info->p.y, info->p.z,
		info->n.x, info->n.y, info->n.z, info->fov);
}

void	add_multi_light(t_parse_info *info, int i, char *line, t_scene *scene)
{
	t_light		*light;
	t_color3	color;

	if (info->single_light == TRUE)
		parse_error("single light", i);
	if (line_scanf(i, line, LSCANF_MULTI_L, &info->p.x, &info->p.y, &info->p.z
			, &info->ratio, &info->c.x, &info->c.y, &info->c.z) != 7)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| info->ratio < 0 || info->ratio > 1
		|| is_point_in_range(&info->p) == FALSE)
		parse_error("out of range", i);
	color = vmul(info->c, RGB_NORMAL);
	light = light_new(&info->p, &color, info->ratio);
	color = vec3(0, 0, 0);
	oadd(&scene->light, object_new(LIGHT, light, &color));
	printf("[%02d, ML]: p(%.2f,%.2f,%.2f) (%.2f) c(%.f,%.f,%.f) \n",
		i, info->p.x, info->p.y, info->p.z, info->ratio,
		info->c.x, info->c.y, info->c.z);
}
