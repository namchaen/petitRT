/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namkim <namkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:31:38 by namkim            #+#    #+#             */
/*   Updated: 2022/11/09 16:11:16 by namkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "petitrt.h"

static void		my_mlx_pixel_put(t_img *img, int x, int y, t_color3 *color);
static t_color3	get_color(t_rt_data *data, float i, float j, t_color3 *color);

static void	my_mlx_pixel_put(t_img *img, int x, int y, t_color3 *color)
{
	char	*dst;

	dst = img->addr
		+ (y * img->line_lenth + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = ((int)color->x << 16) \
							| ((int)color->y << 8) | (int)color->z;
}

static t_color3	get_color(t_rt_data *data, float i, float j, t_color3 *color)
{
	t_scene	*scene;

	scene = data->scene;
	scene->ray = ray_primary(scene->camera, \
		((float)i + ft_frand()) / (data->width - 1), \
			((float)j + ft_frand()) / (data->height - 1));
	return (vadd_(*color, ray_color(scene)));
}

int	do_render(t_rt_data *data)
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
			k = -1;
			while (++k < SAMPLE_SIZE)
				color = get_color(data, i, j, &color);
			color = vmul(vdiv(color, (float)SAMPLE_SIZE), 255.999);
			my_mlx_pixel_put(&data->img, i, data->height - 1 - j, &color);
			i++;
		}
		j--;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	return (0);
}
