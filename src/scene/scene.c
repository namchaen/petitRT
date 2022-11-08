#include "scene.h"
#include "object.h"
#include "parser.h"
#include <stdlib.h>
#include <math.h>

t_scene	*scene_init(char *fname)
{
	t_scene		*scene;

	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL); // TODO : program exit
	scene->light = NULL;
	scene->camera = NULL;
	scene->object = NULL;
	parser(fname, scene);
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
