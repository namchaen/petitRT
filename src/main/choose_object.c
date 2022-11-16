/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 00:36:24 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/16 21:15:39 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

static void	prnt_object(t_object *object);
static void	prnt_plane_info(t_plane *pl, t_color3 *color);
static void	prnt_sphere_info(t_sphere *sp, t_color3 *color);
static void	prnt_cylinder_info(t_cylinder *cy, t_color3 *color);

t_object	*choose_object(int x, int y, t_rt_data *data)
{
	t_ray			ray;
	t_hit_record	rec;
	t_object		*object;
	t_object		*rval;

	rval = data->scene->cameras;
	ray = ray_primary(data->scene->camera, \
		(float)x / (data->width - 1), \
			(float)(data->height - y) / (data->height - 1));
	object = data->scene->object;
	record_init(&rec);
	while (object)
	{
		if (object->hit(object, &ray, &rec))
		{
			rec.tmax = rec.t;
			rval = object;
		}
		object = object->next;
	}
	if (rval != data->scene->cameras)
		prnt_object(rval);
	return (rval);
}

static void	prnt_object(t_object *object)
{
	if (object->type == PL)
		prnt_plane_info(object->element, &object->albedo);
	else if (object->type == SP)
		prnt_sphere_info(object->element, &object->albedo);
	else if (object->type == CY)
		prnt_cylinder_info(object->element, &object->albedo);
}

static void	prnt_plane_info(t_plane *pl, t_color3 *color)
{
	printf("Select plain!\n");
	printf("\tp(%.2f,%.2f,%.2f) n(%.2f,%.2f,%.2f) c(%.2f,%.2f,%.2f)\n",
		pl->point.x, pl->point.y, pl->point.z,
		pl->normal.x, pl->normal.y, pl->normal.z,
		color->x, color->y, color->z);
}

static void	prnt_sphere_info(t_sphere *sp, t_color3 *color)
{
	printf("Select sphere!\n");
	printf("\tp(%.2f,%.2f,%.2f) radius:%.2f c(%.2f,%.2f,%.2f)\n",
		sp->center.x, sp->center.y, sp->center.z, \
		sp->radius, color->x, color->y, color->z);
}

static void	prnt_cylinder_info(t_cylinder *cy, t_color3 *color)
{
	printf("Select cylinder!\n");
	printf("\tp(%.2f,%.2f,%.2f) n(%.2f,%.2f,%.2f) c(%.2f,%.2f,%.2f)\n\
		\b\b\b\b\b\b\b\br:%.2f h:%.2f\n",
		cy->center_base.x, cy->center_base.y, cy->center_base.z,
		cy->normal.x, cy->normal.y, cy->normal.z,
		color->x, color->y, color->z,
		cy->radius, cy->height);
}
