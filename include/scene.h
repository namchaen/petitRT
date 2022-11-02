#ifndef SCENE_H
# define SCENE_H

# include "struct.h"

t_scene		*scene_init(int width, int height);

void    	camera_init(t_camera *cam, float aspect_ratio, t_point3 orig);

#endif
