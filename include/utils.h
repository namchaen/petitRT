/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:29:08 by namkim            #+#    #+#             */
/*   Updated: 2022/11/08 16:55:22 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <mlx.h>
# include "scene.h"	//왜 이건 바로 인식 되지?
# include "struct.h"
# include "keymap.h"

float	ft_frand(void);
int		ft_exit(t_rt_data *data);
int		input_process_init(t_rt_data *data);
int		process_mouse_input(int mousecode, int x, int y, t_rt_data *data);
int		process_key_input(int keycode, t_rt_data *data);

#endif
