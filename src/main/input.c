/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:24:58 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 20:40:34 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"
#include "keymap.h"
#include "struct.h"
#include "scene.h"
#include "util.h"
#include <mlx.h>
#include <math.h>

int	process_mouse_input(int mousecode, int x, int y, t_rt_data *data)
{
	t_camera	*cam;

	(void)x;
	(void)y;
	cam = data->scene->camera;
	if (mousecode == 4 && cam->fov < 177)
		cam->fov += 3.f;
	if (mousecode == 5 && cam->fov > 3)
		cam->fov -= 3.f;
	camera_set(cam, cam->fov, cam->orig);
	do_render(data);
	return (0);
}

int	process_key_input(int keycode, t_rt_data *data)
{
	t_camera	*cam;

	cam = data->scene->camera;
	if (keycode == ESC)
		ft_exit(data);
	else if (keycode <= KEY_UP && keycode >= KEY_LEFT)
		rotate_camera(keycode, cam);
	else if (keycode == KEY_W)
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
