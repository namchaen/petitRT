/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:41:55 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 16:46:11 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <stdio.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

typedef t_vec3	t_point3;
typedef t_vec3	t_color3;

t_vec3	vec3(float x, float y, float z);
t_vec3	point3(float x, float y, float z);
t_vec3	color3(float x, float y, float z);
t_vec3	vmin(t_vec3 v1, t_vec3 v2);
void	vprnt(char *vname, t_vec3 *v);

float	vdot(t_vec3 v1, t_vec3 v2);
t_vec3	vcross(t_vec3 v1, t_vec3 v2);

t_vec3	vadd_(t_vec3 v1, t_vec3 v2);
t_vec3	vsub_(t_vec3 v1, t_vec3 v2);
t_vec3	vmul_(t_vec3 v1, t_vec3 v2);
t_vec3	vdiv_(t_vec3 v1, t_vec3 v2);

t_vec3	vadd(t_vec3 v1, float t);
t_vec3	vsub(t_vec3 v1, float t);
t_vec3	vmul(t_vec3 v1, float t);
t_vec3	vdiv(t_vec3 v1, float t);

float	vnorm2(t_vec3 v);
float	vnorm(t_vec3 v);
t_vec3	vunit(t_vec3 v);

t_vec3	vrotate(float theta, t_vec3 n, t_vec3 v1);

#endif
