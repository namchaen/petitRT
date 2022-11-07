#ifndef PARSER_H
# define PARSER_H

# define BUFFER_SIZE 1024

# include <stdlib.h>

char	*get_next_line(int fd);

int		line_scanf(int i, char *line, const char *fmt, ...);

#endif
