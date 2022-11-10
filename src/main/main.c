/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:28:36 by namkim            #+#    #+#             */
/*   Updated: 2022/11/10 14:13:59 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"

static void	set_width_height(t_bool is_default, int *width, int *height, char **av);
static void	rt_data_init(t_rt_data *data, int width, int height);
static void	my_mlx_pixel_put(t_img *img, int x, int y, t_color3 *color);
static int	main_loop(t_rt_data *data);

int	main(int argc, char *argv[])
{
	int			width;
	int			height;
	t_rt_data	data;

	width = 800;
	height = 600;
	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putendl_fd("./miniRT <filename.rt>", 1);
		exit(1);
	}
	data.scene = scene_init(argv[1]);
	rt_data_init(&data, width, height);
	do_render(&data);
	//mlx_loop_hook(data.mlx, do_render, &data);
	input_process_init(&data);
	mlx_loop(data.mlx);
	return (0);
}

static void	rt_data_init(t_rt_data *data, int width, int height)
{
	float		aspect_ratio;

	data->mlx = mlx_init();
	aspect_ratio = 16.0 / 9.0;
	data->sample_size = SAMPLE_SIZE;
	data->width = width;
	data->height = data->width / aspect_ratio;
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height, "miniRT");
	data->img.ptr = mlx_new_image(data->mlx, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr,
		&data->img.bits_per_pixel, &data->img.line_lenth, &data->img.endian);
}

