#include "scene.h"

void	camera_init(t_camera *cam, float aspect_ratio, const t_point3 orig)
{
	cam->viewport_h = 2.0;
	cam->viewport_w = cam->viewport_h * aspect_ratio;
	cam->focal_length = 1.0;
	cam->orig = orig;
	//camera 의 vector가 갖는 vector...? 이게 정확히 무슨 뜻일까? viewport와의 상대방향?
	cam->horizontal = vec3(cam->viewport_w, 0.0, 0.0);
	cam->vertical = vec3(0.0, cam->viewport_h, 0.0);
	cam->lower_left_corner.x = cam->orig.x
		- (cam->horizontal.x / 2)
		- (cam->vertical.x / 2) - 0;
	cam->lower_left_corner.y = cam->orig.y
		- (cam->horizontal.y / 2)
		- (cam->vertical.y / 2) - 0;
	cam->lower_left_corner.z = cam->orig.z
		- (cam->horizontal.z / 2)
		- (cam->vertical.z / 2)
		- cam->focal_length;
}