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

	theta = 30 * M_PI / 180;
	cam = data->scene->camera;
	if (keycode == ESC)
		ft_exit(data);
	else if (keycode == KEY_UP)
	{
		tmp = vqut_mul(theta, vmul(cam->dir[1], sin(theta)), *cam->dir);
		*cam->dir = vqut_mul(-theta, tmp, vmul(cam->dir[1], sin(-theta)));
	}
	else if (keycode == KEY_DOWN)
	{
		tmp = vqut_mul(-theta, vmul(cam->dir[1], sin(-theta)), *cam->dir);
		*cam->dir = vqut_mul(theta, tmp, vmul(cam->dir[1], sin(theta)));
	}
	else if (keycode == KEY_LEFT)
	{
		tmp = vqut_mul(theta, vmul(cam->dir[2], sin(theta)), *cam->dir);
		*cam->dir = vunit(vqut_mul(-theta, vunit(tmp), vmul(cam->dir[2], sin(-theta))));
	}
	else if (keycode == KEY_RIGHT)
	{
		tmp = vqut_mul(-theta, vmul(cam->dir[2], sin(-theta)), *cam->dir);
		*cam->dir = vunit(vqut_mul(theta, vunit(tmp), vmul(cam->dir[2], sin(theta))));
	}
	camera_init(cam, cam->fov, cam->orig, *cam->dir);
	vprnt("camdir : ", &*cam->dir);
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
