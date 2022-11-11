/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:09:11 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 17:10:17 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3(float x, float y, float z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	point3(float x, float y, float z)
{
	t_point3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_vec3	color3(float x, float y, float z)
{
	t_color3	color;

	color.x = x;
	color.y = y;
	color.z = z;
	return (color);
}

t_vec3	vmin(t_vec3 v1, t_vec3 v2)
{
	if (v1.x > v2.x)
		v1.x = v2.x;
	if (v1.y > v2.y)
		v1.y = v2.y;
	if (v1.z > v2.z)
		v1.z = v2.z;
	return (v1);
}

void	vprnt(char *vname, t_vec3 *v)
{
	printf("%s : %f, %f, %f\n", vname, v->x, v->y, v->z);
}
