/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:10:06 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/16 18:25:02 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <float.h>
#include <limits.h>
#include <math.h>

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
		|| v->z < min || v->z > max
		|| vnorm(*v) <= EPSILON)
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

t_bool	is_point_in_range(t_point3 *point)
{
	if (fabsf(point->x) >= FLT_MAX
		|| fabsf(point->y) >= FLT_MAX
		|| fabsf(point->z) >= FLT_MAX
		|| point->x < LONG_MIN || point->x > LONG_MAX
		|| point->y < LONG_MIN || point->y > LONG_MAX
		|| point->z < LONG_MIN || point->z > LONG_MAX)
		return (FALSE);
	if (fabsf(point->x) <= FLT_MIN)
		point->x = 0;
	if (fabsf(point->y) <= FLT_MIN)
		point->y = 0;
	if (fabsf(point->z) <= FLT_MIN)
		point->z = 0;
	return (TRUE);
}
