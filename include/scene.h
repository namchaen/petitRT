/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:41:13 by namkim            #+#    #+#             */
/*   Updated: 2022/11/14 15:53:39 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "struct.h"
# define THETA 0.21
# define ASPECT_RATIO 0.562500

t_scene		*scene_init(char *fname);
t_camera	*camera_new(const t_point3 orig, const t_vec3 dir, float fov);
t_light		*light_new(t_point3 *light_origin, \
						t_color3 *light_color, float bright_ratio);
void		camera_set(t_camera *cam, float fov, const t_point3 orig);
void		rotate_camera(int keycode, t_camera *cam);
void		move_camera(int keycode, t_camera *cam);

void		move_object(int keycode, t_object *object);
void		rotate_object(int keycode, t_object *object);
void		orbit_camera(t_camera *cam, t_vec3 *move, float sensitivity);

#endif
