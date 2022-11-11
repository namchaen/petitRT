/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:23:44 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 18:26:36 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

static t_bool	in_shadow(t_object *obj, t_ray light_ray, float light_len)
{
	t_hit_record	temp_rec;

	temp_rec.tmin = 0;
	temp_rec.tmax = light_len;
	if (hit(obj, &light_ray, &temp_rec))
		return (TRUE);
	return (FALSE);
}

t_bool	is_in_shadow(const t_scene *scene, \
					const t_light *light, t_vec3 light_dir)
{
	float	light_len;
	t_vec3	v_tmp;
	t_ray	light_ray;

	light_dir = vsub_(light->orig, scene->rec.p);
	light_len = vnorm(light_dir);
	v_tmp = vadd_(scene->rec.p, vmul(scene->rec.normal, EPSILON));
	light_ray = ray_set(&v_tmp, &light_dir);
	return (in_shadow(scene->object, light_ray, light_len));
}
