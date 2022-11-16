/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:10:09 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/16 19:31:11 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "utils.h"

static int	open_file(char *fname);
static void	info_init(t_parse_info *info);
static void	set_ambient_light(t_parse_info *info,
				int i, char *line, t_scene *scene);
static void	*set_add_obj(char *line);

void	parser(char *fname, t_scene *scene)
{
	int				fd;
	int				i;
	char			*line;
	t_parse_info	info;
	t_add_obj		add_obj;

	fd = open_file(fname);
	info_init(&info);
	i = 1;
	line = get_next_line(fd);
	while (line)
	{
		add_obj = set_add_obj(line);
		if (add_obj)
			add_obj(&info, i, line, scene);
		else if (*line != '\n' && *line != '#')
			parse_error("invalid identifier", i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	if (info.single_ambient == FALSE || !scene->camera || !scene->light)
		ft_error("no A or C or L");
}

static int	open_file(char *fname)
{
	int		fd;
	int		len;
	char	*tmp;

	len = ft_strlen(fname);
	tmp = fname + len;
	if (!(*(--tmp) == 't' && *(--tmp) == 'r' && *(--tmp) == '.'))
		ft_error("not .rt file");
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		ft_error("open failed");
	return (fd);
}

static void	info_init(t_parse_info *info)
{
	info->single_ambient = FALSE;
	info->single_camera = FALSE;
	info->single_light = FALSE;
}

static void	*set_add_obj(char *line)
{
	if (*line == 'A')
		return (set_ambient_light);
	else if (*line == 'C')
		return (add_camera);
	else if (*line == 'L')
		return (add_light);
	else if (*line == 'p' && *(line + 1) == 'l')
		return (add_plane);
	else if (*line == 's' && *(line + 1) == 'p')
		return (add_sphere);
	else if (*line == 'c' && *(line + 1) == 'y')
		return (add_cylinder);
	else if (*line == 'l')
		return (add_multi_light);
	return (NULL);
}

static void	set_ambient_light(t_parse_info *info,
				int i, char *line, t_scene *scene)
{
	if (info->single_ambient != FALSE)
		parse_error("redefinition of ambient lighting", i);
	info->single_ambient = TRUE;
	if (line_scanf(i, line, LSCANF_A,
			&info->ratio, &info->c.x, &info->c.y, &info->c.z) != 4)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| info->ratio <= EPSILON || info->ratio > 1)
		parse_error("out of range", i);
	scene->ambient = vmul(vmul(info->c, RGB_NORMAL), info->ratio);
	printf("[%02d AL]: (%.2f) c(%.f,%.f,%.f)\n",
		i, info->ratio, info->c.x, info->c.y, info->c.z);
}
