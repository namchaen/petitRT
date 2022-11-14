/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:16:00 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/14 15:28:37 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	ray_primary(const t_camera *cam, float i, float j)
{
	t_ray	ray;
	t_vec3	u;
	t_vec3	v;

	ray.orig = cam->orig;
	u = vmul(cam->horizontal, i);
	v = vmul(cam->vertical, j);
	ray.dir = vunit(vsub_(vadd_(vadd_(cam->left_bottom, u), v), cam->orig));
	return (ray);
}

t_ray	ray_set(const t_point3 *origin, const t_vec3 *dir)
{
	t_ray	ray;

	ray.orig = *origin;
	ray.dir = vunit(*dir);
	return (ray);
}

t_point3	ray_at(const t_ray *ray, float t)
{
	return (vadd_(ray->orig, vmul(ray->dir, t)));
}

t_color3	ray_color(t_scene *scene)
{
	float		t;

	record_init(&scene->rec);
	if (hit(scene->object, &scene->ray, &scene->rec))
		return (phong_lighting(scene));
	t = 0.5 * (scene->ray.dir.y + 1.0);
	return (vadd_(vmul(color3(1.0, 1.0, 1.0), 1.0 - t),
			vmul(color3(0.5, 0.7, 1.0), t)));
}
