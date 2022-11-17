/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:02:00 by namkim            #+#    #+#             */
/*   Updated: 2022/11/17 09:37:36 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"
#include <stdlib.h>

float	line_space(int k, int sample_size)
{
	return ((float)k / (float)sample_size);
}

int	ft_exit(t_rt_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	printf("=== the end ===\n");
	exit(0);
}

t_bool	is_in_window(int x, int y, t_rt_data *data)
{
	if (x < 0 || x > data->width
		|| y < 0 || y > data->height)
		return (FALSE);
	return (TRUE);
}
