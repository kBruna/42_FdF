/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:14:17 by buehara           #+#    #+#             */
/*   Updated: 2025/12/20 13:53:53 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	translate(int button, int x, int y, void *ptr)
{
	if (button == 1)
		ft_printf("Coord: (%d, %d)\n", x, y);
	(void)ptr;
	return (0);
}

int	main(int argc, char **argv)
{
	t_master	master;

	init_check(argc, argv, &master);
//	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp,
//			&master.img.line_length, &master.img.endian);
	ft_fdf(&master);
	fdf_hook(&master);
	mlx_put_image_to_window(master.mlx.mlx,
		master.mlx.window, master.img.img, 0, 0);
	mlx_loop(master.mlx.mlx);
	return (0);
}
