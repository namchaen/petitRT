#include "scene.h"
#include "object.h"
#include <stdlib.h>

static t_object	*object_init(void)
{
	t_object	*obj;

	obj = create_object(SP, create_sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); // obj 에 구1 추가
	oadd(&obj, create_object(PL, create_plane(point3(0, 0, -5000), vec3(1, 2, 3)), color3 (0, 0, 0.6)));	//plane추가
	oadd(&obj, create_object(SP, create_sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); // obj 에 구2 추가
	oadd(&obj, create_object(SP, create_sphere(point3(0, -1000, 0), 990), color3(1, 1, 1))); // obj 에 구3 추가
	return (obj);
}

t_scene	*scene_init(int width, int height)
{
	t_scene		*scene;
	t_object	*lights;
	float		ka;
	t_point3	orig;
	t_color3	color;
	t_point3	center;

	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL); // TODO : program exit
	camera_init(&scene->camera, 16.0 / 9.0, point3(0, 0, 0));
	scene->object = object_init();
	lights = create_object(LIGHT,
			create_light(point3(0, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmul(color3(1, 1, 1), ka);
	return (scene);
}