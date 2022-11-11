#include "scene.h"
#include <math.h>

void	camera_set(t_camera *cam, float fov, const t_point3 orig)
{
	t_vec3	w;
	float	aspect_ratio;

	aspect_ratio = 16.0 / 9.0;
	w = vmul(cam->dir[0], -1);
	cam->orig = orig;
	cam->fov = fov;
	cam->viewport_h = 2.0 * tan(fov * M_PI / (180.0 * 2));
	cam->viewport_w = cam->viewport_h * aspect_ratio;
	cam->horizontal = vmul(cam->dir[1], cam->viewport_w);
	cam->vertical = vmul(cam->dir[2], cam->viewport_h);
	cam->lower_left_corner = vsub_(cam->orig,
			vadd_(vadd_(vmul(cam->horizontal, 0.5), vmul(cam->vertical, 0.5)),
				w));
}