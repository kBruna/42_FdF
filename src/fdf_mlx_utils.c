/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:01:50 by buehara           #+#    #+#             */
/*   Updated: 2025/12/21 20:26:10 by buehara          ###   ########.fr       */
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
	else if (keycode == XK_w || keycode == XK_a
		|| keycode == XK_d || keycode == XK_s)
		translate(master, keycode);
	else if (keycode == XK_Up || keycode == XK_Down || keycode == XK_e
		|| keycode == XK_Right || keycode == XK_Left || keycode == XK_q
		|| keycode == XK_r)
		rotate(master, keycode);
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
