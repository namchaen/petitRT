#include "scene.h"
#include "object.h"
#include "parser.h"
#include <stdlib.h>
#include <math.h>

static t_object	*object_init(void)
{
	t_object	*obj;

	obj = create_object(SP, create_sphere(point3(0, -1000, 0), 990), color3(1, 1, 1));
	// obj = create_object(SP, create_sphere(point3(-9, 0, -5), 2), color3(0.5, 0, 0)); // obj 에 구1 추가
	//oadd(&obj, create_object(PL, create_plane(point3(0, -10, 0), vec3(0, 1, 0)), color3 (0, 0, 0.6)));	//plane추가
	//oadd(&obj, create_object(SP, create_sphere(point3(-2, 0, -10), 2), color3(0.6, 0.1, 0.1))); // obj 에 구2 추가
	//oadd(&obj, create_object(SP, create_sphere(point3(2, 0, -10), 2), color3(0.1, 0.6, 0.1))); // obj 에 구2 추가
	oadd(&obj, create_object(CY, create_cylinder(point3(-8, -2, -10), vec3(0, 0, 1), 4, 5), color3(0.5, 0.5, 0))); // yellow
	oadd(&obj, create_object(CY, create_cylinder(point3(-3, -2, -10), vec3(1, 0, 0), 4, 5), color3(0, 0.5, 0.5))); // cyan
	oadd(&obj, create_object(CY, create_cylinder(point3(6, -4, -10), vec3(0, 1, 0), 4, 5), color3(0.5, 0, 0.5))); // pink
	return (obj);
}

t_scene	*scene_init(int width, int height)
{
	t_scene		*scene;
	// t_object	*lights;
	float		ka;

	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL); // TODO : program exit
	// camera_init(&scene->camera, 60, point3(0, 6, 15), vec3(0, -0.5, -1));
	// scene->camera = camera_new(point3(0, 6, 15), vec3(0, -0.5, -1), 60);
	// scene->object = object_init();
	// lights = create_object(LIGHT,
	// 		create_light(point3(0, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
	// scene->light = lights;
	// ka = 0.1;
	// scene->ambient = vmul(color3(1, 1, 1), ka);
	scene->light = NULL;
	scene->camera = NULL;
	scene->object = NULL;
	parser("my_simple_0_1.rt", scene);
	return (scene);
}

t_camera	*camera_new(const t_point3 orig, const t_vec3 dir, float fov)
{
	t_camera	*cam;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
	float		aspect_ratio;

	if (!(cam = (t_camera *)malloc(sizeof(t_camera))))
		return (NULL);
	w = vmul(dir, -1);
	if (fabs(vnorm(vcross(vec3(0, 1, 0), w))) <= EPSILON)
		u = vunit(vcross(vec3(1, 0, 0), w));
	else
		u = vunit(vcross(vec3(0, 1, 0), w));
	// u = vunit(vcross(vec3(0, 1, 0), w));
	v = vunit(vcross(w, u));
	aspect_ratio = 16.0 / 9.0;
	cam->orig = orig;
	cam->dir = dir;
	cam->fov = fov;
	cam->viewport_h = 2.0 * tan(fov * M_PI / (180.0 * 2));
	cam->viewport_w = cam->viewport_h * aspect_ratio;
	cam->horizontal = vmul(u, cam->viewport_w);
	cam->vertical = vmul(v, cam->viewport_h);
	cam->lower_left_corner = vsub_(cam->orig,
			vadd_(vadd_(vmul(cam->horizontal, 0.5), vmul(cam->vertical, 0.5)),
				w));
	return (cam);
}

t_light	*light_new(t_point3 *light_origin, t_color3 *light_color, float bright_ratio)
{
	t_light	*light;

	if(!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->orig = *light_origin;
	light->light_color = *light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}
