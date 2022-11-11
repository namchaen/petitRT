/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:51:24 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 20:39:16 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define BUFFER_SIZE 1024

# include "struct.h"
# include <stdlib.h>

# define RGB_NORMAL 0.00392156

# define LSCANF_A "A %f %f,%f,%f"
# define LSCANF_C "C %f,%f,%f %f,%f,%f %f"
# define LSCANF_L "L %f,%f,%f %f %f,%f,%f"
# define LSCANF_PL "pl %f,%f,%f %f,%f,%f %f,%f,%f"
# define LSCANF_SP "sp %f,%f,%f %f %f,%f,%f"
# define LSCANF_CY "cy %f,%f,%f %f,%f,%f %f %f %f,%f,%f"
# define LSCANF_MULTI_C "c %f %f,%f,%f"
# define LSCANF_MULTI_L "l %f,%f,%f %f %f,%f,%f"

typedef struct s_parse_info
{
	t_point3	p;
	t_vec3		n;
	t_color3	c;
	float		fov;
	float		radius;
	float		height;
	float		diameter;
	float		ratio;
	t_bool		single_camera;
	t_bool		single_light;
	t_bool		single_ambient;
}				t_parse_info;

typedef void	(*t_add_obj)(
			t_parse_info *, int i, char *, t_scene *scene);

char	*get_next_line(int fd);

int		line_scanf(int i, char *line, const char *fmt, ...);

void	parser(char *fname, t_scene *scene);

void	parse_error(char *msg, int line_num);
t_bool	is_vec_in_range(t_vec3 *v, int min, int max);
t_bool	is_color_in_range(t_color3 *color);

void	add_light(t_parse_info *info, int i, char *line, t_scene *scene);
void	add_camera(t_parse_info *info, int i, char *line, t_scene *scene);

void	add_plane(t_parse_info *info, int i, char *line, t_scene *scene);
void	add_sphere(t_parse_info *info, int i, char *line, t_scene *scene);
void	add_cylinder(t_parse_info *info, int i, char *line, t_scene *scene);

#endif
