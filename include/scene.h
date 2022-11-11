#ifndef SCENE_H
# define SCENE_H

# include "struct.h"

t_scene		*scene_init(char *fname);
t_camera	*camera_new(const t_point3 orig, const t_vec3 dir, float fov);
t_light		*light_new(t_point3 *light_origin, t_color3 *light_color, float bright_ratio);

void		camera_set(t_camera *cam, float fov, const t_point3 orig);

#endif
