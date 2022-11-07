#include "parser.h"
#include "libft.h"

void	parse_error(char *msg, int line_num)
{
	ft_putstr_fd("Error\nparse error.", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd(" (line: ", 1);
	ft_putnbr_fd(line_num, 1);
	ft_putstr_fd(")\n", 1);
	exit(1);
}

t_bool	is_vec_in_range(t_vec3 *v, int min, int max)
{
	if (v->x < min || v->x > max
		|| v->y < min || v->y > max
		|| v->z < min || v->z > max)
		return (FALSE);
	return (TRUE);
}

t_bool	is_color_in_range(t_color3 *color)
{
	if (color->x < 0 || color->x > 255
		|| color->y < 0 || color->y > 255
		|| color->z < 0 || color->z > 255)
		return (FALSE);
	return (TRUE);
}