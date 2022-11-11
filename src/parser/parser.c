#include "parser.h"
#include "libft.h"

static void	ft_error(char *msg);
static int	check_filename(char *fname);
static void	set_ambient_light(t_parse_info *info, int i, char *line, t_color3 *ambient);

void	parser(char *fname, t_scene *scene)
{
	int				fd;
	int				i;
	char			*line;
	t_parse_info	info;

	if (check_filename(fname) != 0)
		ft_error("not .rt file");
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		ft_error("open failed");
	info.single_ambient = FALSE;
	info.single_camera = FALSE;
	info.single_light = FALSE;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "A", 1) == 0)
			set_ambient_light(&info, i, line, &scene->ambient);
		else if (ft_strncmp(line, "C", 1) == 0)
			add_camera(&info, i, line, &scene->camera);
		else if (ft_strncmp(line, "L", 1) == 0)
			add_light(&info, i, line, &scene->light);
		else if (ft_strncmp(line, "pl", 2) == 0)
			add_plane(&info, i, line, &scene->object);
		else if (ft_strncmp(line, "sp", 2) == 0)
			add_sphere(&info, i, line, &scene->object);
		else if (ft_strncmp(line, "cy", 2) == 0)
			add_cylinder(&info, i, line, &scene->object);
		else if (*line != '\n' && *line != '#')
			parse_error("invalid identifier", i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (line)
		free(line);
	if (info.single_ambient == FALSE|| !scene->camera || !scene->light)
		ft_error("no A or C or L");
}

static int	check_filename(char *fname)
{
	int	len;

	len = ft_strlen(fname);
	fname += len;
	if (*(--fname) == 't' && *(--fname) == 'r' && *(--fname) == '.')
		return (0);
	return (-1);
}


static void	ft_error(char *msg)
{
	ft_putstr_fd("Error\n", 1);
	ft_putendl_fd(msg, 1);
	exit(1);
}

static void	set_ambient_light(t_parse_info *info, int i, char *line, t_color3 *ambient)
{
	if (info->single_ambient != FALSE)
		parse_error("redefinition of ambient lighting", i);
	info->single_ambient = TRUE;
	if (line_scanf(i, line, LSCANF_A, &info->ratio, &info->c.x, &info->c.y, &info->c.z) != 4)
		parse_error("unmatched number", i);
	if (is_color_in_range(&info->c) == FALSE
		|| info->ratio <= EPSILON)
		parse_error("out of range", i);
	info->c = vmul(info->c, 0.00392156);
	*ambient = vmul(info->c, info->ratio);
}
