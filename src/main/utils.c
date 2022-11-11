/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:02:00 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 18:05:43 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"
#include <stdlib.h>

float	ft_frand(void)
{
	return ((float)rand() / (float)RAND_MAX);
}

int	ft_exit(t_rt_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	printf("=== the end ===\n");
	exit(0);
}
