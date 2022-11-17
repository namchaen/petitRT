/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   petitrt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:30:57 by namkim            #+#    #+#             */
/*   Updated: 2022/11/17 09:37:36 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PETITRT_H
# define PETITRT_H

# include <mlx.h>
# include "scene.h"
# include "ray.h"
# include "object.h"
# include "libft.h"
# include "keymap.h"
# include <stdlib.h>

# define WIDTH 800
# define SENSTV 300

/* main/utils.c */
float		line_space(int k, int sample_size);
int			ft_exit(t_rt_data *data);
t_bool		is_in_window(int x, int y, t_rt_data *data);

int			input_process_init(t_rt_data *data);

t_object	*choose_object(int x, int y, t_rt_data *data);

int			do_render(t_rt_data *data);

#endif
