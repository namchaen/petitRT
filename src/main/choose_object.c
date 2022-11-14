/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 00:36:24 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/13 07:06:02 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_object	*choose_object(int x, int y, t_rt_data *data)
{
	t_ray			ray;
	t_hit_record	rec;
	t_object		*object;
	t_object		*rval;

	rval = NULL;
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
	return (rval);
}
