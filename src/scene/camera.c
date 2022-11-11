/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:11:12 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 20:27:33 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "keymap.h"
#include <math.h>

void	camera_set(t_camera *cam, float fov, const t_point3 orig)
{
	t_vec3	w;
	float	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	w = vmul(cam->dir[0], -1);
	cam->orig = orig;
	cam->fov = fov;
	cam->viewport_h = 2.0 * tan(fov * M_PI / (180.0 * 2));
	cam->viewport_w = cam->viewport_h * aspect_ratio;
	cam->horizontal = vmul(cam->dir[1], cam->viewport_w);
	cam->vertical = vmul(cam->dir[2], cam->viewport_h);
	cam->lower_left_corner = vsub_(cam->orig,
			vadd_(vadd_(vmul(cam->horizontal, 0.5), vmul(cam->vertical, 0.5)),
				w));
}

void	rotate_camera(int keycode, t_camera *cam)
{
	float	theta;
	t_vec3	*target;
	t_vec3	*target2;
	t_vec3	*axis;

	theta = THETA;
	target = &cam->dir[0];
	if (keycode == KEY_DOWN || keycode == KEY_RIGHT)
		theta = -THETA;
	if (keycode == KEY_UP || keycode == KEY_DOWN)
	{
		target2 = &cam->dir[2];
		axis = &cam->dir[1];
	}
	else
	{
		target2 = &cam->dir[1];
		axis = &cam->dir[2];
	}
	*target = vunit(vrotate(theta, *axis, *target));
	*target2 = vunit(vrotate(theta, *axis, *target2));
}

void	move_camera(float *axis, float distance)
{
	*axis += distance;
}
