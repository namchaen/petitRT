/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:38:58 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/16 15:47:06 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <math.h>
#include <float.h>

#include <stdio.h>

static double	set_i(const char *str)
{
	double	rval;
	long	n;

	rval = 0;
	n = 0;
	while (*str >= '0' && *str <= '9')
	{
		rval *= 10;
		n = (n * 10) + (*str - '0');
		if (n > 100000000000)
		{
			rval += n;
			n = 0;
		}
		if (rval >= FLT_MAX)
			return (FLT_MAX);
		str++;
	}
	if (n)
		rval += n;
	return (rval);
}

static double	set_d(const char *str)
{
	double	rval;
	double	digit;
	long	n;

	rval = 0;
	digit = 1;
	n = 0;
	while (digit * 0.1 > FLT_MIN && *str >= '0' && *str <= '9')
	{
		digit *= 0.1;
		n = (n * 10) + (*str - '0');
		if (n > 100000000000)
		{
			rval += (n * digit);
			n = 0;
		}
		str++;
	}
	if (n)
		rval += (n * digit);
	return (rval);
}

double	ft_atof(const char *str)
{
	double	rval;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign = -1;
	}
	if (*str < '0' || *str > '9')
		return (0);
	rval = set_i(str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (rval == FLT_MAX || *str != '.')
		return (sign * rval);
	rval += set_d(++str);
	return (sign * rval);
}
