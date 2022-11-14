/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:11:32 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 17:14:10 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "ray.h"
#include <stdlib.h>
#include <math.h>

t_object	*object_new(t_object_type type, void *element, t_color3 *albedo)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = *albedo;
	if (type == SP)
		new->hit = hit_sphere;
	else if (type == PL)
		new->hit = hit_plane;
	else if (type == CY)
		new->hit = hit_cylinder;
	return (new);
}

t_sphere	*sphere_new(t_point3 *center, float radius)
{
	t_sphere	*sp;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = *center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_plane	*plane_new(t_point3 *point, t_vec3 *normal)
{
	t_plane	*pl;

	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->point = *point;
	pl->normal = vdiv(*normal, vnorm(*normal));
	return (pl);
}

t_cylinder	*cylinder_new(t_point3 *point, \
							t_vec3 *normal, float radius, float height)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->center_base = *point;
	cy->normal = vdiv(*normal, vnorm(*normal));
	cy->h = vmul(cy->normal, height);
	cy->center_top = vadd_(*point, cy->h);
	cy->center = vadd_(*point, vmul(cy->h, 0.5));
	cy->radius = radius;
	cy->radius2 = cy->radius * cy->radius;
	cy->height = height;
	return (cy);
}
