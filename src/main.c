/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:23:36 by buehara           #+#    #+#             */
/*   Updated: 2025/11/24 22:16:40 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minilibx/mlx.h"
#include "math.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*window;
	t_data	view;
	
	mlx = mlx_init();
	window = mlx_new_window(mlx, 500, 500, "FdF");
	view.img = mlx_new_image(mlx, 500, 500);
	view.addr = mlx_get_data_addr(view.img, &view.bits_per_pixel, &view.line_length, &view.endian);
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++)
			my_mlx_pixel_put(&view, M_PI*i, M_PI*j, 0xFFFFFFFF);
	}
	for (int i = 50; i > 0; i--){
		for (int j = 50; j > 0; j--)
			my_mlx_pixel_put(&view, M_PI*i, M_PI*j, 0xFFFFFFFF);
	}
	mlx_put_image_to_window(mlx, window, view.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
