#include "scene.h"
#include <math.h>

void	camera_init(t_camera *cam, float fov, const t_point3 orig, const t_vec3 dir)
{
	t_vec3	w;
	float	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	cam->orig = orig;
	cam->dir[0] = vunit(dir);
	cam->fov = fov;
	w = vmul(dir, -1);
	if (fabs(vnorm(vcross(vec3(0, 1, 0), w))) <= EPSILON)
		cam->dir[1] = vunit(vcross(vec3(1, 0, 0), w));
	else
		cam->dir[1] = vunit(vcross(vec3(0, 1, 0), w));
	cam->dir[2] = vunit(vcross(w, cam->dir[1]));
	cam->viewport_h = 2.0 * tan(fov * M_PI / (180.0 * 2));
	cam->viewport_w = cam->viewport_h * aspect_ratio;
	cam->horizontal = vmul(cam->dir[1], cam->viewport_w);
	cam->vertical = vmul(cam->dir[2], cam->viewport_h);
	cam->lower_left_corner = vsub_(cam->orig,
			vadd_(vadd_(vmul(cam->horizontal, 0.5), vmul(cam->vertical, 0.5)),
				w));
				//vmul(w, cam->focal_length)));
}
