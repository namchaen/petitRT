/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:18:31 by namkim            #+#    #+#             */
/*   Updated: 2022/11/16 20:33:58 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "object.h"
#include "parser.h"
#include <stdlib.h>
#include <math.h>

t_scene	*scene_init(char *fname)
{
	t_scene		*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->light = NULL;
	scene->camera = NULL;
	scene->cameras = NULL;
	scene->object = NULL;
	parser(fname, scene);
	return (scene);
}

static void	camera_dir_set(t_camera *cam, t_vec3 w)
{
	if (fabs(vnorm(vcross(vec3(0, 1, 0), w))) > EPSILON)
	{
		cam->dir[1] = vunit(vcross(vec3(0, 1, 0), w));
		cam->dir[2] = vunit(vcross(w, cam->dir[1]));
	}
	else
	{
		cam->dir[2] = vunit(vcross(vec3(0, 0, -1), w));
		cam->dir[1] = vunit(vcross(w, cam->dir[2]));
	}
}

t_camera	*camera_new(const t_point3 orig, const t_vec3 dir, float fov)
{
	t_camera	*cam;
	t_vec3		w;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->dir[0] = vunit(dir);
	w = vunit(vmul(*cam->dir, -1));
	camera_dir_set(cam, w);
	cam->orig = orig;
	cam->fov = fov;
	cam->viewport_w = 2.0 * tan(fov * M_PI / (180 * 2));
	cam->viewport_h = cam->viewport_w * ASPECT_RATIO;
	cam->horizontal = vmul(cam->dir[1], cam->viewport_w);
	cam->vertical = vmul(cam->dir[2], cam->viewport_h);
	cam->left_bottom = vsub_(cam->orig,
			vadd_(vadd_(vmul(cam->horizontal, 0.5), vmul(cam->vertical, 0.5)),
				w));
	return (cam);
}

t_light	*light_new(t_point3 *light_origin, \
					t_color3 *light_color, float bright_ratio)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->orig = *light_origin;
	light->light_color = *light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}
