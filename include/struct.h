#ifndef RT_INT_H
# define RT_INT_H

# include "vec3.h"
# include <stdio.h> //printf

# define EPSILON 1e-3 // 0.001 float
// # define EPSILON 1e-6 // 0.000001
# define LUMEN 3

typedef t_vec3 t_point3;
typedef t_vec3 t_color3;

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

typedef struct	s_camera
{
	t_point3	orig;
	//t_point3	normal;
	t_point3	lower_left_corner;
	t_vec3		horizontal;
	t_vec3		vertical;
	//t_vec3		u;
	//t_vec3		v;
	//t_vec3		w;
	float		focal_length;
	//floatvertical		time[2]; // shutter open, close times
	float		viewport_h;
	float		viewport_w;
	// TODO : viewport -> fov(Horizontal field of view in degrees in range)
	//struct t_camera	*next;
	//struct t_camera	*prev;
}				t_camera;

typedef struct		s_light
{
	t_point3	orig;
	t_color3	light_color;
	float		bright_ratio;
}				t_light;

typedef struct	s_ray
{
	t_point3	orig;
	t_vec3		dir;
	float		tm;
}				t_ray;

typedef struct s_hit_record
{
	t_point3	p; // 교점의 좌표
	t_vec3		normal; // 교점에서의 법선
	float		t; // 광선의 원점과 교점 사이의 거리
	//float		u;
	//float		v;
	float		tmin;
	float		tmax;
	t_bool		front_face;
	// 그 외 교점에서의 색깔 등 추가적으로 필요한 정보는 이후에 추가
	t_color3	albedo;  // 반사율
	//void		*mat_ptr;
}			t_hit_record;

typedef struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color3		albedo; // 반사율
	void	(*object_handler)(void *element);
}				t_object;

typedef struct  s_sphere
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
	//t_point3	point;
	t_point3	center;
	t_point3	center_top;
	t_point3	center_base;
	t_vec3		h;
	t_vec3		normal;
	float		radius;
	float		radius2;
	float		height;
}				t_cylinder;

typedef struct	s_scene
{
	t_camera		camera;
	t_object		*object;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
}				t_scene;

typedef struct		s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenth;
	int		endian;
}					t_img;

typedef struct 	s_rt_data
{
	void	*mlx;
	void	*mlx_win;
	int		width;
	int		height;
	t_img	img;
	t_scene	*scene;
}						t_rt_data;

#endif