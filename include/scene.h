#ifndef SCENE_H
# define SCENE_H

# include "struct.h"

t_scene		*scene_init(int width, int height);

void		camera_init(t_camera *cam, float fov, const t_point3 orig, const t_vec3 dir);

#endif
