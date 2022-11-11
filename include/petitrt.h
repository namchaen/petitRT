/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   petitrt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:30:57 by namkim            #+#    #+#             */
/*   Updated: 2022/11/11 19:52:34 by chaejkim         ###   ########.fr       */
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

/* main/utils.c */
float	ft_frand(void);
int		ft_exit(t_rt_data *data);
int		input_process_init(t_rt_data *data);
int		process_mouse_input(int mousecode, int x, int y, t_rt_data *data);
int		process_key_input(int keycode, t_rt_data *data);

int		do_render(t_rt_data *data);

#endif
