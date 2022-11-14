/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:17:33 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/14 12:30:47 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

static t_color3	point_light_get(const t_scene *scene, const t_light *light);
static t_vec3	reflect(t_vec3 v, t_vec3 n);
static t_color3	cal_specular(const t_scene *scene, \
						const t_light *light, t_vec3 light_dir);
static t_bool	is_in_shadow(const t_scene *scene, t_vec3 light_dir);

t_color3	phong_lighting(const t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color3(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		light_color = vadd_(light_color,
				point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = vadd_(light_color, scene->ambient);
	return (vmin(vmul_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}

static t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vsub_(v, vmul(n, vdot(v, n) * 2)));
}

static t_color3	cal_specular(const t_scene *scene, \
						const t_light *light, t_vec3 light_dir)
{
	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	float		spec;

	view_dir = vunit(vmul(scene->ray.dir, -1));
	reflect_dir = reflect(vmul(light_dir, -1), scene->rec.normal);
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), KSN);
	specular = vmul(light->light_color, KS * spec);
	return (specular);
}

static t_color3	point_light_get(const t_scene *scene, const t_light *light)
{
	t_vec3		light_dir;
	float		kd;
	t_color3	diffuse;
	t_color3	specular;
	float		brightness;

	light_dir = vsub_(light->orig, scene->rec.p);
	if (is_in_shadow(scene, light_dir))
		return (vadd_(color3(0, 0, 0), scene->ambient));
	light_dir = vunit(light_dir);
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	diffuse = vmul(light->light_color, kd);
	specular = cal_specular(scene, light, light_dir);
	brightness = light->bright_ratio * LUMEN;
	return (vmul(vadd_(vadd_(diffuse, specular), scene->ambient), brightness));
}

static t_bool	is_in_shadow(const t_scene *scene, t_vec3 light_dir)
{
	float			light_len;
	t_vec3			v_tmp;
	t_ray			light_ray;
	t_hit_record	temp_rec;

	light_len = vnorm(light_dir);
	v_tmp = vadd_(scene->rec.p, vmul(light_dir, EPSILON));
	light_ray = ray_set(&v_tmp, &light_dir);
	temp_rec.tmin = 0;
	temp_rec.tmax = light_len;
	if (hit(scene->object, &light_ray, &temp_rec))
		return (TRUE);
	return (FALSE);
}
