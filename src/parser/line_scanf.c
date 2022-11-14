/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_scanf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:10:04 by chaejkim          #+#    #+#             */
/*   Updated: 2022/11/14 15:25:43 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdarg.h>

static int	lscanf(int i, char *line, const char *fmt, va_list *arg_ptr);
static void	skip_isspace(const char **fmt, char **line);
static int	do_scan(char **line, const char fmt, va_list *arg_ptr);
static int	scan_f(char **line, float *f);

int	line_scanf(int i, char *line, const char *fmt, ...)
{
	va_list	arg_ptr;
	int		scan_cnt;

	va_start(arg_ptr, fmt);
	scan_cnt = lscanf(i, line, fmt, &arg_ptr);
	va_end(arg_ptr);
	return (scan_cnt);
}

static int	lscanf(int i, char *line, const char *fmt, va_list *arg_ptr)
{
	int		scan_cnt;

	scan_cnt = 0;
	while (*fmt && *line)
	{
		skip_isspace(&fmt, &line);
		while (*fmt != '%' && *fmt && *line && *fmt++ != *line++)
			parse_error("unmatched char", i);
		if (*fmt == '%')
		{
			if (*fmt)
			fmt++;
			if (do_scan(&line, *(fmt++), arg_ptr) != 0)
				parse_error("unvalid num", i);
			scan_cnt += 1;
		}
	}
	skip_isspace(&fmt, &line);
	if (*fmt || *line)
		parse_error("unmatched char", i);
	return (scan_cnt);
}

static void	skip_isspace(const char **fmt, char **line)
{
	while (ft_isspace(**fmt))
		(*fmt)++;
	while (ft_isspace(**line))
		(*line)++;
}

static int	do_scan(char **line, const char fmt, va_list *arg_ptr)
{
	int	rval;

	rval = 0;
	if (fmt == 'f')
		rval = scan_f(line, va_arg(*arg_ptr, void *));
	else
		printf("warning!! line_scanf only has %%f\n");
	return (rval);
}

static int	scan_f(char **line, float *f)
{
	*f = ft_atof(*line);
	if (**line == '+' || **line == '-')
		(*line)++;
	while (**line >= '0' && **line <= '9')
		(*line)++;
	if (**line == '.')
		(*line)++;
	while (**line >= '0' && **line <= '9')
		(*line)++;
	if (*f == 0 && (**line == '0' || (**line == '+' && *(*line + 1) == '0')))
		return (1);
	return (0);
}
