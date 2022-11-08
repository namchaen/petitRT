/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:28:36 by namkim            #+#    #+#             */
/*   Updated: 2022/11/08 16:55:56 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"

static void set_width_height(t_bool is_default, int *width, int *height, char **av);
static void rt_data_init(t_rt_data *data, int width, int height);
static void	my_mlx_pixel_put(t_img *img, int x, int y, t_color3 *color);
static int main_loop(t_rt_data *data);

int	main(int argc, char *argv[])
{
	int			width;
	int			height;
	t_rt_data	data;

	width = 800;
	height = 600;
	if (argc != 2)
	{
		//ft_error("./miniRT <filename.rt>");
		ft_putstr_fd("Error\n", 1);
		ft_putendl_fd("./miniRT <filename.rt>", 1);
		exit(1);
	}
	data.scene = scene_init(argv[1]);
	rt_data_init(&data, width, height);
	mlx_loop_hook(data.mlx, ft_draw, &data);
	ft_draw(&data);
	input_process_init(&data);
	// mlx_hook(data.mlx_win, RED_CROSS, 0, ft_exit, &data);
	// mlx_hook(data.mlx_win, KEY_PRESS, 0, process_key_input, &data);
	// mlx_hook(data.mlx_win, MOUSE_PRESS, 0, process_mouse_input, &data);	//mouse press
	// mlx_hook(data.mlx_win, MOUSE_RELEASE, 0, process_mouse_input, &data);
	mlx_loop(data.mlx);
	return (0);
}
static void rt_data_init(t_rt_data *data, int width, int height)
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

static void	my_mlx_pixel_put(t_img *img, int x, int y, t_color3 *color)
{
	char	*dst;

	dst = img->addr
		+ (y * img->line_lenth + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = ((int)color->x << 16) | ((int)color->y << 8) | (int)color->z;
}

int	ft_draw(t_rt_data *data)
{
	int			i;
	int			j;
	int			k;
	t_color3	color;
	t_scene		*scene;

	scene = data->scene;
	j = data->height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < data->width)
		{
			color = vec3(0, 0, 0);
			k = 0;
			while (k < SAMPLE_SIZE)
			{
				scene->ray = ray_primary(scene->camera, \
					((float)i + ft_frand()) / (data->width - 1), \
						((float)j + ft_frand()) / (data->height - 1));
				color = vadd_(color, ray_color(scene));
				k++;
			}
			color = vdiv(color, (float)SAMPLE_SIZE);
			color = vmul(color, 255.999);
			my_mlx_pixel_put(&data->img, i, data->height - 1 - j, &color);
			i++;
		}
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
		j--;
	}
	//mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	return (0);
}

static int main_loop(t_rt_data *data)
{
	ft_draw(data);
	return (0);
}
