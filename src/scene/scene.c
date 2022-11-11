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
	float		aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	if (!(cam = (t_camera *)malloc(sizeof(t_camera))))
		return (NULL);
	cam->dir[0] = vunit(dir);
	w = vunit(vmul(*cam->dir, -1));
	if (fabs(vnorm(vcross(vec3(0, 1, 0), w))) > EPSILON)
	{
		cam->dir[1] = vunit(vcross(vec3(0, 1, 0), w));
		cam->dir[2] = vunit(vcross(w, cam->dir[1]));
	}
	//else if (w.y < 0)
	//{
	//	cam->dir[1] = vunit(vcross(vec3(0, 0, 1), w));
	//	cam->dir[2] = vunit(vcross(w, cam->dir[1]));
	//}
	else
	{
		cam->dir[2] = vunit(vcross(vec3(0, 0, -1), w));
		cam->dir[1] = vunit(vcross(w, cam->dir[2]));
	}
	cam->orig = orig;
	cam->fov = fov;
	cam->viewport_h = 2.0 * tan(fov * M_PI / (180.0 * 2));
	cam->viewport_w = cam->viewport_h * aspect_ratio;
	cam->horizontal = vmul(cam->dir[1], cam->viewport_w); //u
	cam->vertical = vmul(cam->dir[2], cam->viewport_h); //v
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
