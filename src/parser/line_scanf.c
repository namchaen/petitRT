#include "parser.h"
#include "libft.h"
#include <stdarg.h>

static int	lscanf(int i, char *line, const char *fmt, va_list *arg_ptr);
static int	do_scan(char **line, const char fmt, va_list *arg_ptr);
static int	scan_f(char **line, float *f);
static int	scan_obj_type(char **line, int *type);

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
		while (ft_isspace(*fmt))
			fmt++;
		while (ft_isspace(*line))
			line++;
		if (*fmt == '%')
		{
			fmt++;
			if (do_scan(&line, *(fmt++), arg_ptr) != 0)
				parse_error("unvalid num", i);
			scan_cnt += 1;
		}
		else if (*fmt && *line && *fmt++ != *line++)
			parse_error("unmatched char", i);
	}
	return (scan_cnt);
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
