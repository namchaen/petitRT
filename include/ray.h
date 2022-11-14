/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:47:56 by namkim            #+#    #+#             */
/*   Updated: 2022/11/14 12:02:37 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "struct.h"
# include <math.h>
# define KSN 64 // shininess value
# define KS 0.7 // specular strength

t_ray		ray_primary(const t_camera *cam, float t1, float t2);
t_ray		ray_set(const t_point3 *origin, const t_vec3 *dir);
t_point3	ray_at(const t_ray *ray, float t);
t_color3	ray_color(t_scene *scene);

t_color3	phong_lighting(const t_scene *scene);

void		record_init(t_hit_record *rec);
void		record_set_face_normal(t_ray *r, t_hit_record *rec);

t_bool		hit(t_object *object, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_object *object, t_ray *ray, t_hit_record *rec);

t_bool		hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec);

#endif
