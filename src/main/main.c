/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:28:36 by namkim            #+#    #+#             */
/*   Updated: 2022/11/16 20:11:22 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"

static void	rt_data_init(t_rt_data *data, int width);

int	main(int argc, char *argv[])
{
	t_rt_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putendl_fd("./miniRT <filename.rt>", 1);
		exit(1);
	}
	data.scene = scene_init(argv[1]);
	rt_data_init(&data, WIDTH);
	do_render(&data);
	input_process_init(&data);
	mlx_loop(data.mlx);
	return (0);
}

static void	rt_data_init(t_rt_data *data, int width)
{
	data->mlx = mlx_init();
	data->sample_size = SAMPLE_SIZE;
	data->width = width;
	data->height = data->width * ASPECT_RATIO;
	data->mlx_win = mlx_new_window(data->mlx,
			data->width, data->height, "miniRT");
	data->img.ptr = mlx_new_image(data->mlx, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bits_per_pixel,
			&data->img.line_lenth, &data->img.endian);
	data->anti_ali = TRUE;
	data->left_mouse.press = FALSE;
	data->left_mouse.pos = point3(0, 0, 0);
}
