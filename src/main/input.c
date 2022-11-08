/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:24:58 by namkim            #+#    #+#             */
/*   Updated: 2022/11/08 17:11:59 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"
#include "keymap.h"
#include "struct.h"
#include "scene.h"
#include "util.h"
#include <mlx.h>

/*
object 종류 : camera, light, sphere, plain, cylinder
movement 종류 : 좌표이동 / rotation // 밝기조절 (light)

rotation불가 : light, sphere

*/

int	process_mouse_input(int mousecode, int x, int y, t_rt_data *data)
{
	t_camera	*cam;

	(void)x;
	(void)y;
	cam = &(data->scene->camera);
	printf("mousecode : %d\n", mousecode);
	printf("x: %d, y: %d\n", x, y);
	if (mousecode == 4)
		cam->fov += 3;
	if (mousecode == 5)
		cam->fov -= 3;
	camera_init(cam, cam->fov, cam->orig, cam->dir);
	ft_draw(data);
	return (0);
}

int	process_key_input(int keycode, t_rt_data *data)
{
	t_camera	*cam;

	cam = &(data->scene->camera);
	if (keycode == ESC)
		ft_exit(data);
	else if (keycode == KEY_UP)	// 위
	{
		cam->dir = vunit(vadd_(data->scene->camera.dir, vec3(0, 0.2, 0)));
		camera_init(cam, cam->fov, cam->orig, cam->dir);
		ft_draw(data);
	}
	else if (keycode == KEY_DOWN)	//아래
	{
		data->scene->camera.dir	= vunit(vadd_(data->scene->camera.dir, vec3(0, -0.2, 0)));
		camera_init(cam, cam->fov, cam->orig, cam->dir);
		ft_draw(data);
	}
	else if (keycode == KEY_LEFT)	// <-
	{
		data->scene->camera.dir	= vunit(vadd_(data->scene->camera.dir, vec3(-0.2, 0, 0)));
		camera_init(cam, cam->fov, cam->orig, cam->dir);
		ft_draw(data);
	}
	else if (keycode == KEY_RIGHT)	// ->
	{
		data->scene->camera.dir	= vunit(vadd_(data->scene->camera.dir, vec3(0.2, 0, 0)));
		camera_init(cam, cam->fov, cam->orig, cam->dir);
		ft_draw(data);
	}
	else if (keycode == KEY_W)
	{
		(t_cylinder *)(data->scene->object->element)->center = vadd_((t_cylinder *)data->scene->object->element->center, vec3(0, 1, 0));
	}
	else
		printf("keycode : %d\n", keycode);
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
