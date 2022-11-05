/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:38:58 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/03 23:43:49 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <math.h>
#include <stdio.h> //d/safaweh

static size_t	get_len(long long_i)
{
	size_t	len;

	len = 1;
	if (long_i < 0)
		long_i *= -1;
	while (long_i > 9)
	{
		len++;
		long_i /= 10;
	}
	return (len);
}

static float	set_d(const char *str)
{
	float	rval;
	int		cnt;
	float	digit;

	cnt = -1;
	rval = 0;
	digit = 1;
	while (++cnt < 7 && *str >= '0' && *str <= '9')
	{
		rval = rval * 10 + (*str - '0');
		str++;
		digit *= 0.1; 
	}
	rval *= digit;
	return (rval);
}

float	ft_atof(const char *str)
{
	float	rval;
	long	i;
	int		len;

	while (ft_isspace(*str))
		str++;
	i = ft_strtol(str);
	len = get_len(i);
	if (*str == '+' || *str == '-')
		len += 1;
	str += len;
	rval = i;
	if (i == LONG_MAX || i == LONG_MIN)
	{
		while (*str >= '0' && *str <= '9')
		{
			rval = rval * 10;
			str++;
		}
	}
	if (*str != '.')
		return (rval);
	printf("(ft_atof) i : %f\n", rval);
	if (i < 0)
		return (rval - set_d(++str));
	return (rval + set_d(++str));
}