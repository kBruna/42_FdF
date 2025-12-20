/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:01:50 by buehara           #+#    #+#             */
/*   Updated: 2025/12/19 21:18:38 by buehara          ###   ########.fr       */
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
	if else (keycode == XK_1)
		
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
	master->img.img = mlx_new_image(master->mlx.mlx, WIDTH, HEIGHT);
	if (!master->img.img)
	{
		mlx_destroy_window(master->mlx.mlx, master->mlx.window);
		mlx_destroy_display(master->mlx.mlx);
		free(master->mlx.mlx);
		return (FALSE);
	}
	master->img.steep = 0;
	return (TRUE);
}
