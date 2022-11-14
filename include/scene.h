/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:41:13 by namkim            #+#    #+#             */
/*   Updated: 2022/11/13 06:43:23 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "struct.h"
# define THETA 0.2

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
