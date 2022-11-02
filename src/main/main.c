#include <mlx.h>
//#include "mlx.h"
#include "scene.h"
#include "ray.h"
#include "object.h"
#include "libft.h" // atoi

static void set_width_height(t_bool is_default, int *width, int *height, char **av);
static void rt_data_init(t_rt_data *data, int width, int height);
static void	my_mlx_pixel_put(t_img *img, int x, int y, t_color3 *color);
static int ft_draw(t_rt_data *data);
static int main_loop(t_rt_data *data);

int	main(int argc, char *argv[])
{
	int			width;
	int			height;
	t_rt_data	data;

	set_width_height(argc!=3, &width, &height, argv);
	data.scene = scene_init(width, height);
	rt_data_init(&data, width, height);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}

static void set_width_height(t_bool is_default, int *width, int *height, char **av)
{
	if (!is_default)
	{
		*width = ft_atoi(av[1]);
		*height = ft_atoi(av[2]);
	}
	if (is_default || !*width || !*height)
	{
		*width = 400;
		*height = 300;
	}
}

static void rt_data_init(t_rt_data *data, int width, int height)
{
	float		aspect_ratio;

	data->mlx = mlx_init();
	aspect_ratio = 16.0 / 9.0;
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

static int ft_draw(t_rt_data *data)
{
	int			i;
	int			j;
	t_ray		ray;
	t_color3		color;
	t_scene		*scene;

	scene = data->scene;
	j = data->height - 1;
	while (j >= 0)
	{
		i = 0;
		ft_putstr_fd("\rScanlines remaining: ", 1);
		ft_putnbr_fd(j, 1);
		ft_putchar_fd(' ', 1);
		while (i < data->width)
		{
			scene->ray = ray_primary(&scene->camera,
				(float)i / (data->width - 1), (float)j / (data->height - 1));
			color = vmul(ray_color(scene), 255.999);
			my_mlx_pixel_put(&data->img, i, data->height - 1 - j, &color);
			i++;
		}
		j--;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	return (0);
}

static int main_loop(t_rt_data *data)
{
	ft_draw(data);
	return (0);
}
