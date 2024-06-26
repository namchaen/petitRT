/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:11:12 by namkim            #+#    #+#             */
/*   Updated: 2022/11/16 18:49:19 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "keymap.h"
#include <math.h>

void	camera_set(t_camera *cam, float fov, const t_point3 orig)
{
	t_vec3	w;

	w = vmul(cam->dir[0], -1);
	cam->orig = orig;
	cam->fov = fov;
	cam->viewport_w = 2.0 * tan(fov * M_PI / (180 * 2));
	cam->viewport_h = cam->viewport_w * ASPECT_RATIO;
	cam->horizontal = vmul(cam->dir[1], cam->viewport_w);
	cam->vertical = vmul(cam->dir[2], cam->viewport_h);
	cam->left_bottom = vsub_(cam->orig,
			vadd_(vadd_(vmul(cam->horizontal, 0.5), vmul(cam->vertical, 0.5)),
				w));
	printf("camera set! (fov : %f)\n", cam->fov);
	vprnt("\tcam->orig", &cam->orig);
	vprnt("\tcam->dir[0]", &cam->dir[0]);
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
	camera_set(cam, cam->fov, cam->orig);
}

void	move_camera(int keycode, t_camera *cam)
{
	if (keycode == KEY_W)
		cam->orig.y += 1;
	else if (keycode == KEY_A)
		cam->orig.x -= 1;
	else if (keycode == KEY_S)
		cam->orig.y -= 1;
	else if (keycode == KEY_D)
		cam->orig.x += 1;
	else if (keycode == KEY_Z)
		cam->orig.z -= 1;
	else if (keycode == KEY_X)
		cam->orig.z += 1;
	camera_set(cam, cam->fov, cam->orig);
}

void	orbit_camera(t_camera *cam, t_vec3 *move, float sensitivity)
{
	float		theta[2];

	theta[0] = 0;
	theta[1] = 0;
	if (move->x)
		theta[0] = move->x / sensitivity;
	if (move->y)
		theta[1] = move->y / sensitivity;
	if (fmaxf(fabs(theta[0]), fabs(theta[1])) < DEGREE)
		return ;
	if (fabs(theta[0]) > fabs(theta[1]))
	{
		cam->dir[0] = vunit(vrotate(theta[0], cam->dir[2], cam->dir[0]));
		cam->dir[1] = vunit(vrotate(theta[0], cam->dir[2], cam->dir[1]));
		cam->orig = vrotate(theta[0], cam->dir[2], cam->orig);
	}
	else
	{
		cam->dir[0] = vunit(vrotate(theta[1], cam->dir[1], cam->dir[0]));
		cam->dir[2] = vunit(vrotate(theta[1], cam->dir[1], cam->dir[2]));
		cam->orig = vrotate(theta[1], cam->dir[1], cam->orig);
	}
	camera_set(cam, cam->fov, cam->orig);
}
