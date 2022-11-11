/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:21:36 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/11 18:27:58 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	record_init(t_hit_record *rec)
{
	rec->tmin = EPSILON;
	rec->tmax = INFINITY;
}

void	record_set_face_normal(t_ray *r, t_hit_record *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vmul(rec->normal, -1);
}
