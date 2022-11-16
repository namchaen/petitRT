/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 00:36:01 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/16 20:39:12 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "keymap.h"

static void	move_plane(int keycode, t_plane *pl);
static void	move_sphere(int keycode, t_sphere *sp);
static void	move_cylinder(int keycode, t_cylinder *cy);
static void	cylinder_set(t_cylinder *cy);

void	move_object(int keycode, t_object *object)
{
	if (object->type == CAMERA)
		move_camera(keycode, object->element);
	else if (object->type == SP)
		move_sphere(keycode, object->element);
	else if (object->type == PL)
		move_plane(keycode, object->element);
	else if (object->type == CY)
		move_cylinder(keycode, object->element);
}

static void	move_plane(int keycode, t_plane *pl)
{
	if (keycode == KEY_W)
		pl->point.y += 1;
	else if (keycode == KEY_A)
		pl->point.x -= 1;
	else if (keycode == KEY_S)
		pl->point.y -= 1;
	else if (keycode == KEY_D)
		pl->point.x += 1;
	else if (keycode == KEY_Z)
		pl->point.z -= 1;
	else if (keycode == KEY_X)
		pl->point.z += 1;
}

static void	move_sphere(int keycode, t_sphere *sp)
{
	if (keycode == KEY_W)
		sp->center.y += 1;
	else if (keycode == KEY_A)
		sp->center.x -= 1;
	else if (keycode == KEY_S)
		sp->center.y -= 1;
	else if (keycode == KEY_D)
		sp->center.x += 1;
	else if (keycode == KEY_Z)
		sp->center.z -= 1;
	else if (keycode == KEY_X)
		sp->center.z += 1;
}

static void	move_cylinder(int keycode, t_cylinder *cy)
{
	if (keycode == KEY_W)
		cy->center.y += 1;
	else if (keycode == KEY_A)
		cy->center.x -= 1;
	else if (keycode == KEY_S)
		cy->center.y -= 1;
	else if (keycode == KEY_D)
		cy->center.x += 1;
	else if (keycode == KEY_Z)
		cy->center.z -= 1;
	else if (keycode == KEY_X)
		cy->center.z += 1;
	cylinder_set(cy);
}

static void	cylinder_set(t_cylinder *cy)
{
	cy->center_top = vadd_(cy->center, vmul(cy->h, 0.5));
	cy->center_base = vsub_(cy->center, vmul(cy->h, 0.5));
}
