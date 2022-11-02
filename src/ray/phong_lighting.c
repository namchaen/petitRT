#include "ray.h"
#include <math.h>

static t_color3	point_light_get(const t_scene *scene, const t_light *light);
static t_vec3	reflect(t_vec3 v, t_vec3 n);

t_color3	phong_lighting(const t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color3(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT)
		{
			light_color = vadd_(light_color, point_light_get(scene, lights->element));
		}
		lights = lights->next;
	}
	light_color = vadd_(light_color, scene->ambient);
	return (vmin(vmul_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}

static t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vsub_(v, vmul(n, vdot(v, n) * 2)));
}

t_bool	in_shadow(t_object *obj, t_ray light_ray, float light_len)
{
	t_hit_record	temp_rec; // 필요 없을 시 지우기

	temp_rec.tmin = 0;
	temp_rec.tmax = light_len;
	if (hit(obj, &light_ray, &temp_rec))
		return (TRUE);
	return (FALSE);
}


static t_color3	point_light_get(const t_scene *scene, const t_light *light)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	float		kd; // diffuse의 강도

	float		light_len;
	t_ray		light_ray;
	float		brightness;

	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	float		spec;
	float		ksn;
	float		ks;

	t_vec3		v_tmp;

	light_dir = vsub_(light->orig, scene->rec.p);
	light_len = vnorm(light_dir);
	v_tmp = vadd_(scene->rec.p, vmul(scene->rec.normal, EPSILON));
	light_ray = ray_set(&v_tmp, &light_dir);
	//if (in_shadow(scene->object, light_ray, light_len))
	//	return (color3(0, 0.5, 0));
	light_dir = vunit(light_dir); //교점에서 출발하여 광원을 향하는 벡터(정규화 됨)
	// cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
	diffuse = vmul(light->light_color, kd);

	view_dir = vunit(vmul(scene->ray.dir, -1));
	reflect_dir = reflect(vmul(light_dir, -1), scene->rec.normal);
	ksn = 64; // shininess value
	ks = 0.7; // specular strength
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmul(light->light_color, ks * spec);

	brightness = light->bright_ratio * LUMEN;
	return (vmul(vadd_(vadd_(diffuse, specular), scene->ambient), brightness));
}
