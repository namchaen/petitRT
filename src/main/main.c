/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:28:36 by namkim            #+#    #+#             */
/*   Updated: 2022/11/13 06:31:46 by chaejkim         ###   ########.fr       */
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
	float		aspect_ratio;

	data->mlx = mlx_init();
	aspect_ratio = 16.0 / 9.0;
	data->sample_size = SAMPLE_SIZE;
	data->width = width;
	data->height = data->width / aspect_ratio;
	data->mlx_win = mlx_new_window(data->mlx,
			data->width, data->height, "miniRT");
	data->img.ptr = mlx_new_image(data->mlx, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bits_per_pixel,
			&data->img.line_lenth, &data->img.endian);
	data->left_mouse.press = FALSE;
	data->left_mouse.pos = point3(0, 0, 0);
}
