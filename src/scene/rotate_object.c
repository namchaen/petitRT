/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 00:35:57 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/16 20:06:17 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "keymap.h"

static void	rotate_plane(int keycode, t_plane *pl);
static void	rotate_cylinder(int keycode, t_cylinder *cy);
static void	cylinder_set(t_cylinder *cy);

void	rotate_object(int keycode, t_object *object)
{
	if (object->type == CAMERA)
		rotate_camera(keycode, object->element);
	else if (object->type == PL)
		rotate_plane(keycode, object->element);
	else if (object->type == CY)
		rotate_cylinder(keycode, object->element);
}

static void	rotate_plane(int keycode, t_plane *pl)
{
	float	theta;
	t_vec3	axis;

	theta = THETA;
	if (keycode == KEY_DOWN || keycode == KEY_RIGHT)
		theta = -THETA;
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		axis = vec3(1, 0, 0);
	else
		axis = vec3(0, 1, 0);
	pl->normal = vunit(vrotate(theta, axis, pl->normal));
}

static void	rotate_cylinder(int keycode, t_cylinder *cy)
{
	float	theta;
	t_vec3	axis;

	theta = THETA;
	if (keycode == KEY_DOWN || keycode == KEY_RIGHT)
		theta = -THETA;
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		axis = vec3(1, 0, 0);
	else
		axis = vec3(0, 1, 0);
	cy->normal = vunit(vrotate(theta, axis, cy->normal));
	cylinder_set(cy);
}

static void	cylinder_set(t_cylinder *cy)
{
	cy->h = vmul(cy->normal, cy->height);
	cy->center_top = vadd_(cy->center, vmul(cy->h, 0.5));
	cy->center_base = vsub_(cy->center, vmul(cy->h, 0.5));
}
