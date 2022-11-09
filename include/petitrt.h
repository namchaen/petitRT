/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   petitrt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:30:57 by namkim            #+#    #+#             */
/*   Updated: 2022/11/09 16:09:01 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PETITRT_H
# define PETITRT_H

# include <mlx.h>
# include "scene.h"
# include "ray.h"
# include "object.h"
# include "libft.h"
# include "utils.h"
# include <stdlib.h>

int	do_render(t_rt_data *data);

#endif
