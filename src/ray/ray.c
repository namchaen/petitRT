#include "ray.h"
#include <math.h>

t_ray	ray_primary(const t_camera *cam, float u, float v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	ray.dir = vunit(vsub_(vadd_(vadd_(cam->lower_left_corner, vmul(cam->horizontal, u)), vmul(cam->vertical, v)), cam->orig));
	return (ray);

}

t_ray	ray_set(const t_point3 *origin, const t_vec3 *dir)
{
	t_ray	ray;

	ray.orig = *origin;
	ray.dir = vunit(*dir); // 안전빵 나중에 속도 리뷰
	return (ray);
}

t_point3	ray_at(const t_ray *ray, float t)
{
	t_point3	p;

	p.x = ray->orig.x + t * ray->dir.x;
	p.y = ray->orig.y + t * ray->dir.y;
	p.z = ray->orig.z + t * ray->dir.z;
	return (p);
}

t_color3	ray_color(t_scene *scene)
{
	float		t;

	record_init(&scene->rec);
	if (hit(scene->object, &scene->ray, &scene->rec))
		return (phong_lighting(scene));
	t = 0.5 * (scene->ray.dir.y + 1.0);
	return (vadd_(vmul(color3(1.0, 1.0, 1.0), 1.0 - t), vmul(color3(0.5, 0.7, 1.0), t)));
}
