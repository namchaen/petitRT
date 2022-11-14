/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:15:01 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/14 11:57:12 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_bool	hit(t_object *object, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_anything;

	hit_anything = FALSE;
	while (object)
	{
		if (object->hit(object, ray, rec))
		{
			hit_anything = TRUE;
			rec->tmax = rec->t;
		}
		object = object->next;
	}
	return (hit_anything);
}
