/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:24:58 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 16:24:40 by chaejkim         ###   ########.fr       */
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
	camera_set(cam, cam->fov, cam->orig);
	do_render(data);
	return (0);
}

int	process_key_input(int keycode, t_rt_data *data)
{
	t_camera	*cam;
	float		theta;

	theta = 0.2;
	cam = data->scene->camera;
	if (keycode == ESC)
		ft_exit(data);
	else if (keycode == KEY_UP)
	{
		cam->dir[0] = vunit(vrotate(theta, cam->dir[1], cam->dir[0]));
		cam->dir[2] = vunit(vrotate(theta, cam->dir[1], cam->dir[2]));
	}
	else if (keycode == KEY_DOWN)
	{
		cam->dir[0] = vunit(vrotate(-theta, cam->dir[1], cam->dir[0]));
		cam->dir[2] = vunit(vrotate(-theta, cam->dir[1], cam->dir[2]));
	}
	else if (keycode == KEY_LEFT)
	{
		cam->dir[0] = vunit(vrotate(theta, cam->dir[2], cam->dir[0]));
		cam->dir[1] = vunit(vrotate(theta, cam->dir[2], cam->dir[1]));
	}
	else if (keycode == KEY_RIGHT)
	{
		cam->dir[0] = vunit(vrotate(-theta, cam->dir[2], cam->dir[0]));
		cam->dir[1] = vunit(vrotate(-theta, cam->dir[2], cam->dir[1]));
	}
	camera_set(cam, cam->fov, cam->orig);
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
