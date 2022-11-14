/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:24:58 by namkim            #+#    #+#             */
/*   Updated: 2022/11/14 16:54:52 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"
#include <math.h>

static int	key_input(int keycode, t_rt_data *data);
static int	mouse_press_input(int mousecode, int x, int y, t_rt_data *data);
static int	mouse_release_input(int mousecode, int x, int y, t_rt_data *data);
static int	mouse_motion_input(int x, int y, t_rt_data *data);

int	input_process_init(t_rt_data *data)
{
	mlx_hook(data->mlx_win, RED_CROSS, 0, ft_exit, data);
	mlx_hook(data->mlx_win, KEY_PRESS, 0, key_input, data);
	mlx_hook(data->mlx_win, MOUSE_PRESS, 0, mouse_press_input, data);
	mlx_hook(data->mlx_win, MOUSE_RELEASE, 0, mouse_release_input, data);
	mlx_hook(data->mlx_win, MOUSE_MOTION, 0, mouse_motion_input, data);
	return (0);
}

static int	key_input(int keycode, t_rt_data *data)
{
	t_camera	*cam;

	cam = data->scene->camera;
	if (keycode == ESC && data->this == NULL)
		ft_exit(data);
	else if (keycode == ESC)
		data->this = NULL;
	else if (keycode <= KEY_UP && keycode >= KEY_LEFT)
	{
		if (data->this)
			rotate_object(keycode, data->this);
		else
			rotate_camera(keycode, cam);
	}
	if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D
		|| keycode == KEY_Z || keycode == KEY_X)
	{
		if (data->this)
			move_object(keycode, data->this);
		else
			move_camera(keycode, cam);
	}
	do_render(data);
	return (0);
}

static int	mouse_press_input(int mousecode, int x, int y, t_rt_data *data)
{
	t_camera	*cam;

	(void)x;
	(void)y;
	cam = data->scene->camera;
	if (mousecode == LEFT_CLICK && is_in_window(x, y, data))
	{
		data->left_mouse.press = TRUE;
		data->left_mouse.pos = point3(x, y, 0);
		return (0);
	}
	if (mousecode == RIGHT_CLICK && is_in_window(x, y, data))
	{
		data->this = choose_object(x, y, data);
		return (0);
	}
	if (mousecode == SCROLL_UP && cam->fov < 177)
		cam->fov += 3.f;
	else if (mousecode == SCROLL_DOWN && cam->fov > 3)
		cam->fov -= 3.f;
	camera_set(cam, cam->fov, cam->orig);
	do_render(data);
	return (0);
}

static int	mouse_release_input(int mousecode, int x, int y, t_rt_data *data)
{
	(void)x;
	(void)y;
	if (mousecode == LEFT_CLICK)
		data->left_mouse.press = FALSE;
	return (0);
}

static int	mouse_motion_input(int x, int y, t_rt_data *data)
{
	t_camera	*cam;
	t_vec3		move;

	(void)x;
	(void)y;
	cam = data->scene->camera;
	if (data->left_mouse.press)
	{
		move = vsub_(point3(x, y, 0), data->left_mouse.pos);
		data->left_mouse.pos = point3(x, y, 0);
		orbit_camera(data->scene->camera, &move, SENSTV);
		do_render(data);
	}
	return (0);
}
