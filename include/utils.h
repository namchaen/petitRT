/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:29:08 by namkim            #+#    #+#             */
/*   Updated: 2022/11/05 17:14:07 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <mlx.h>
# include "scene.h"	//왜 이건 바로 인식 되지?
# include "struct.h"

float	ft_frand(void);
int		ft_exit(t_rt_data *data);

#endif
