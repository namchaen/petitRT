/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:38:58 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/11 17:03:15 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

long	ft_strtol(const char *str)
{
	long	sign;
	long	tmp;
	long	sum;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	sum = 0;
	tmp = 0;
	while (*str >= '0' && *str <= '9')
	{
		tmp = (sum * 10) + sign * (*str - '0');
		if (sum > 0 && tmp < 0)
			return (LONG_MAX);
		if (sum < 0 && tmp > 0)
			return (LONG_MIN);
		sum = tmp;
		str++;
	}
	return (sum);
}
