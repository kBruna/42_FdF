/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:01:50 by buehara           #+#    #+#             */
/*   Updated: 2025/12/20 19:07:46 by buehara          ###   ########.fr       */
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
	master->projection = view;
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
	return (0);
}

void	fdf_hook(t_master *master)
{
	mlx_hook(master->mlx.window, 2, 1L << 0, key_map, &master->mlx);
	mlx_hook(master->mlx.window, 17, 1L << 17, close_program, &master->mlx);
	mlx_hook(master->mlx.window, 4, 1L << 2, translate, &master->mlx);
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
