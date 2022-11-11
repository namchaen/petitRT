/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:45:34 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 16:47:23 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "struct.h"

t_object	*create_object(t_object_type type, void *element, t_color3 albedo);
t_light		*create_light(t_point3 light_origin, \
							t_color3 light_color, float bright_ratio);
t_sphere	*create_sphere(t_point3 center, float radius);
t_plane		*create_plane(t_point3 point, t_vec3 normal);
t_cylinder	*create_cylinder(t_point3 point, \
							t_vec3 normal, float diameter, float height);

t_object	*object_new(t_object_type type, void *element, t_color3 *albedo);
t_light		*light_new(t_point3 *light_origin, \
						t_color3 *light_color, float bright_ratio);
t_sphere	*sphere_new(t_point3 *center, float radius);
t_plane		*plane_new(t_point3 *point, t_vec3 *normal);
t_cylinder	*cylinder_new(t_point3 *point, \
							t_vec3 *normal, float diameter, float height);

void		oadd(t_object **list, t_object *new);
t_object	*olast(t_object *list);

#endif
