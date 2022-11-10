/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:24:58 by namkim            #+#    #+#             */
/*   Updated: 2022/11/09 23:52:45 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"
#include "keymap.h"
#include "struct.h"
#include "scene.h"
#include "util.h"
#include <mlx.h>
#include <math.h>

/*
object 종류 : camera, light, sphere, plain, cylinder
movement 종류 : 좌표이동 / rotation // 밝기조절 (light)
rotation : wasdzx
move : up/right/left/어쩌구

rotation불가 : light, sphere
*/
int	process_mouse_input(int mousecode, int x, int y, t_rt_data *data)
{
	t_camera	*cam;
	t_object	*this;

	(void)x;
	(void)y;
	cam = data->scene->camera;
	if (mousecode == 4)
		cam->fov += 3;
	if (mousecode == 5)
		cam->fov -= 3;
	camera_init(cam, cam->fov, cam->orig, *cam->dir);
	do_render(data);
	return (0);
}

int	process_key_input(int keycode, t_rt_data *data)
{
	t_camera	*cam;
	t_vec3		tmp;
	float		theta;

	// theta = 30 * M_PI / 180;
	// theta = 0.21;
	// theta = M_PI * 0.5;
	// theta = 0.2;
	theta = 0.6;
	cam = data->scene->camera;
	if (keycode == ESC)
		ft_exit(data);
	else if (keycode == KEY_UP)
	{
		// if (cam->dir[1].x < 0)
		// {
		// 	// tmp = cam->dir[2];
		// 	// cam->dir[2] = tmp;
		// 	// cam->dir[1] = tmp;
		// 	*cam->dir = vunit(vqut_rotate(theta, vmul(cam->dir[1], -1), *cam->dir));
		// }
		// else
		// 	*cam->dir = vunit(vqut_rotate(theta, cam->dir[1], *cam->dir));
		*cam->dir = vunit(vqut_rotate(theta, cam->dir[1], *cam->dir));
		// tmp = vqut_mul(theta, vmul(cam->dir[1], sin(theta)), *cam->dir);
		// *cam->dir = vunit(vmul_qut(-theta, tmp, vmul(cam->dir[1], sin(-theta))));
	}
	else if (keycode == KEY_DOWN)
	{
		*cam->dir = vunit(vqut_rotate(-theta, cam->dir[1], *cam->dir));
		// tmp = vqut_mul(-theta, vmul(cam->dir[1], sin(-theta)), *cam->dir);
		// *cam->dir = vunit(vmul_qut(theta, tmp, vmul(cam->dir[1], sin(theta))));
	}
	else if (keycode == KEY_LEFT)
	{
		*cam->dir = vunit(vqut_rotate(theta, cam->dir[2], *cam->dir));
		// tmp = vqut_mul(theta, vmul(cam->dir[2], sin(theta)), *cam->dir);
		// *cam->dir = vunit(vmul_qut(-theta, tmp, vmul(cam->dir[2], sin(-theta))));
	}
	else if (keycode == KEY_RIGHT)
	{
		*cam->dir = vunit(vqut_rotate(-theta, cam->dir[2], *cam->dir));
		// tmp = vqut_mul(-theta, vmul(cam->dir[2], sin(-theta)), *cam->dir);
		// *cam->dir = vunit(vmul_qut(theta, tmp, vmul(cam->dir[2], sin(theta))));
	}
	camera_init(cam, cam->fov, cam->orig, *cam->dir);
	vprnt("cam->dir[0]", &cam->dir[0]);
	vprnt("cam->dir[1]", &cam->dir[1]);
	vprnt("cam->dir[2]", &cam->dir[2]);
	vprnt("camdir", &*cam->dir);
	do_render(data);
	return (0);
}

int	input_process_init(t_rt_data *data)
{
	mlx_hook(data->mlx_win, RED_CROSS, 0, ft_exit, data);
	mlx_hook(data->mlx_win, KEY_PRESS, 0, process_key_input, data);
	mlx_hook(data->mlx_win, MOUSE_PRESS, 0, process_mouse_input, data);
	mlx_hook(data->mlx_win, MOUSE_RELEASE, 0, process_mouse_input, data);
	return (0);
}
