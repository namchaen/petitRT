/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:02:00 by namkim            #+#    #+#             */
/*   Updated: 2022/11/05 17:10:53 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

float	ft_frand(void)
{
	return ((float)rand() / (float)RAND_MAX);
}

int	ft_exit(t_rt_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	printf("=== the end ===\n"); //
	exit(0);
}
