#include "scene.h"
#include <math.h>

void	camera_init(t_camera *cam, float fov, const t_point3 orig, const t_vec3 dir)
{
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;
	float	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	//vfov = 60;
	//cam->orig = vec3(0, 6, 15);
	//dir = vec3(0.14, -0.5, -1);
	cam->orig = orig;
	cam->dir = dir;
	cam->fov = fov;
	w = vmul(dir, -1);
	u = vunit(vcross(vec3(0, 1, 0), w));
	v = vunit(vcross(w, u));
	cam->viewport_h = 2.0 * tan(fov * M_PI / (180.0 * 2));
	cam->viewport_w = cam->viewport_h * aspect_ratio;
	//cam->focal_length = 1.0;
	//cam->horizontal = vmul(u, cam->focal_length * cam->viewport_w);
	//cam->vertical = vmul(v, cam->focal_length * cam->viewport_h);
	cam->horizontal = vmul(u, cam->viewport_w);
	cam->vertical = vmul(v, cam->viewport_h);
	cam->lower_left_corner = vsub_(cam->orig,
			vadd_(vadd_(vmul(cam->horizontal, 0.5), vmul(cam->vertical, 0.5)),
				w));
				//vmul(w, cam->focal_length)));
}
