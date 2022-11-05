#include "parser.h"
#include "libft.h"
#include <stdarg.h>
#include <stdio.h> //printf

static void	test_scanf(void)
{
	int	fd;
	int	i;
	float	f[3];
	char	*line;

	fd = open("test_scanf.txt", O_RDONLY);
	if (fd == -1)
	{
		write(1, "open failed\n", 12);
		return ;
	}
	i = 0;
	line = get_next_line(fd);
	line_scanf(i, line, "%f,%f,%f\n", &f[0], &f[1], &f[2]);
	free(line);
	printf("line [%02d]: %f,%f,%f\n", i, f[0], f[1], f[2]);
	//A 0.2 255,255,255
	//C -50,0,20 0,0,0 70
	//L -40,0,30 0.7 255,255,255
	//pl 0,0,0 0,1.0,0 255,0,225
	//sp 0,0,20 20 255,0,0
	//cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
}

static int	do_scan(char **line, const char fmt, va_list *arg_ptr);
static int	scan_f(char **line, float *f);
static int	scan_obj_type(char **line, int *type);

int	line_scanf(int i, char *line, const char *fmt, ...)
{
	va_list	arg_ptr;
	int		scan_cnt;

	scan_cnt = 0;
	va_start(arg_ptr, fmt);
	while (*fmt && *line)
	{
		while (ft_isspace(*fmt) && *fmt != '\n')
			fmt++;
		while (*fmt && *line && *fmt != '%')
		{
			// printf("*fmt:%c*line:%c\n", *fmt, *line);
			if (*fmt++ != *line++)
			{
				printf("Error\nparse error. unmatched (line: %d)\n", i);
				exit(1);
			}
		}
		if (*fmt == '%')
		{
			fmt++;
			if (do_scan(&line, *(fmt++), &arg_ptr) != 0)
			{
				printf("Error\nparse error. num (line: %d)\n", i);
				exit(1);
			}
			scan_cnt += 1;
		}
	}
	// printf("*fmt:%c *line:%c\n", *fmt, *line);
	va_end(arg_ptr);
	return (scan_cnt);
}

static int	do_scan(char **line, const char fmt, va_list *arg_ptr)
{
	int	rval;

	rval = 0;
	if (fmt == 'f')
		rval = scan_f(line, va_arg(*arg_ptr, void *));
	else
		rval = printf("warning!! scanf only has %%f\n");
	return (rval);
}

static int	scan_f(char **line, float *f)
{
	while (ft_isspace(**line))
		(*line)++;
	*f = ft_atof(*line);
	if (**line == '+' || **line == '-')
		(*line)++;
	while (**line >= '0' && **line <= '9')
		(*line)++;
	if (**line == '.')
		(*line)++;
	while (**line >= '0' && **line <= '9')
		(*line)++;
	// printf("%f\n", *f);
	if (*f == 0 && (**line != '0' || (**line != '+' && *(*line + 1) != '0')))
		return (1);
	return (0);
}

// static int	scan_obj_type(char **line, int *type)
// {
// 	char	buf[3];
// 	int		i;

// 	i = 0;
// 	fmt++;
// 	while (ft_isspace(**line))
// 		(*line)++;
// 	while (**line && !ft_isspace(**line))
// 	{
// 		buf[i++] = **line;
// 		(*line)++;
// 	}
// 	buf[i] = '\0';
// 	if (ft_strcmp(buf, "A"))
// 		*type = AMBIENT_LIGHT;
// 	else if (ft_strcmp(buf, "C"))
// 		*type = CAMERA;
// 	else if (ft_strcmp(buf, "L"))
// 		*type = LIGHT;
// 	else if (ft_strcmp(buf, "pl"))
// 		*type = SP;
// 	else if (ft_strcmp(buf, "sp"))
// 		*type = PL;
// 	else if (ft_strcmp(buf, "cy"))
// 		*type = CY;
// 	else
// 	{
// 		printf("parse error. invalid identifier `%s'\n", %buf);
// 		return (1);
// 	}
// 	return (0);
// }
