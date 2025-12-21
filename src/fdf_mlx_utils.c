/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:01:50 by buehara           #+#    #+#             */
/*   Updated: 2025/12/20 21:34:52 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (data->steep)
		ft_void_swap(&x, &y, sizeof(int));
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	select_projection(t_master *master, int view)
{
	master->camera.projection = view;
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	ft_fdf(master);
}

void	zoom_projection(t_master *master, int keycode)
{
	float	add_zoom;

	if (master->rows > 20 && master->cols > 20)
		add_zoom = 0.5;
	else
		add_zoom = 2;
	if (keycode == XK_o && master->camera.zoom > 1)
		master->camera.zoom -= add_zoom;
	else if (keycode == XK_i)
		master->camera.zoom += add_zoom;
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	ft_fdf(master);
}

void	translate(t_master *master, int keycode)
{
	if (keycode == XK_w)
		master->camera.y_add -= 2;
	else if (keycode == XK_s)
		master->camera.y_add += 2;
	if (keycode == XK_d)
		master->camera.x_add += 2;
	else if (keycode == XK_a)
		master->camera.x_add -= 2;
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	ft_fdf(master);
}

int	key_map(int keycode, t_master *master)
{
	if (keycode == XK_Escape)
		close_program(master);
	else if (keycode == XK_1)
		select_projection(master, TOP_VIEW);
	else if (keycode == XK_2)
		select_projection(master, X_VIEW);
	else if (keycode == XK_3)
		select_projection(master, Y_VIEW);
	else if (keycode == XK_0)
		select_projection(master, ISO);
	else if (keycode == XK_i || keycode == XK_o)
		zoom_projection(master, keycode);
	else if (keycode == XK_w || keycode == XK_a ||
		keycode == XK_d || keycode == XK_s)
		translate(master, keycode);
	return (0);
}

void	fdf_hook(t_master *master)
{
	mlx_hook(master->mlx.window, 2, 1L << 0, key_map, &master->mlx);
	mlx_hook(master->mlx.window, 17, 1L << 17, close_program, &master->mlx);
}

int	ft_mlx_init(t_master *master)
{
	master->mlx.mlx = mlx_init();
	if (!master->mlx.mlx)
		return (FALSE);
	master->mlx.window = mlx_new_window(master->mlx.mlx, WIDTH, HEIGHT, "FdF");
	if (!master->mlx.window)
	{
		mlx_destroy_display(master->mlx.mlx);
		free(master->mlx.mlx);
		return (FALSE);
	}
	master->img.steep = 0;
	return (TRUE);
}
