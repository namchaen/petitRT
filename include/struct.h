/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:55:53 by namkim            #+#    #+#             */
/*   Updated: 2022/11/14 15:28:42 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "vec3.h"
# include <stdio.h>
# include <stdlib.h>

# define EPSILON 1e-3
# define LUMEN 3
# define SAMPLE_SIZE 1
# define RED_CROSS 17
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define ESC 53

typedef t_vec3	t_point3;
typedef t_vec3	t_color3;

typedef enum e_bool
{
	FALSE = 0,
	TRUE
}				t_bool;

typedef enum e_object_type
{
	CAMERA,
	AMBIENT_LIGHT,
	LIGHT,
	SP,
	PL,
	CY
}				t_object_type;

typedef struct s_camera
{
	t_point3	orig;
	t_vec3		dir[3];
	float		fov;
	t_point3	left_bottom;
	t_vec3		horizontal;
	t_vec3		vertical;
	float		viewport_h;
	float		viewport_w;
}				t_camera;

typedef struct s_light
{
	t_point3	orig;
	t_color3	light_color;
	float		bright_ratio;
}				t_light;

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
	float		tm;
}				t_ray;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	float		t;
	float		tmin;
	float		tmax;
	t_bool		front_face;
	t_color3	albedo;
}			t_hit_record;

typedef struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color3		albedo;
	enum e_bool		(*hit)(struct s_object *, t_ray *, t_hit_record *);
}				t_object;

typedef struct s_sphere
{
	t_point3	center;
	float		radius;
	float		radius2;
}				t_sphere;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
}				t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_point3	center_top;
	t_point3	center_base;
	t_vec3		h;
	t_vec3		normal;
	float		radius;
	float		radius2;
	float		height;
}				t_cylinder;

typedef struct s_scene
{
	t_camera		*camera;
	t_object		*object;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
}				t_scene;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenth;
	int		endian;
}					t_img;

typedef struct s_mouse
{
	t_bool		press;
	t_point3	pos;
}				t_mouse;

typedef struct s_rt_data
{
	void		*mlx;
	void		*mlx_win;
	int			sample_size;
	int			width;
	int			height;
	t_img		img;
	t_scene		*scene;
	t_mouse		left_mouse;
	t_object	*this;
}			t_rt_data;

typedef struct s_eqtn
{
	float	a;
	float	half_b;
	float	c;
	float	discriminant;
	float	sqrtd;
	float	root;
	float	root1;
}			t_eqtn;

#endif
