/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:14:17 by buehara           #+#    #+#             */
/*   Updated: 2025/12/14 21:15:31 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	init_check(int argc, char **argv, t_master *master)
{
	int			fd;

	fd = open_map(argc, argv);
	if (fd == -1)
	{
		perror("Error opening file");
		exit (ERROR);
	}
	matrix_init(master, fd);
	fd = open_map(argc, argv);
	if (fd == -1)
	{
		matrix_error(master->mcolor, master);
		exit (ERROR);
	}
	if (!matrix_fill(fd, master))
	{
		perror("Error filling matrix");
		exit (ERROR);
	}
	if(!ft_mlx_init(master))
	{
		perror("Error Initializing MLX Lib");
		exit (ERROR);
	}
}	
/*
void	matrix_print(t_master master)
{
	t_axis	id;

	id = (t_axis){0};
	while (id.y < master.rows)
	{
		id.x = 0;
		while (id.x < master.cols)
		{
			ft_printf("%d ", master.matrix[id.y][id.x]);
			id.x++;
		}
		ft_printf("\n");
		id.y++;
	}
	ft_printf("\n");
}

void	mcolor_print(t_master master)
{
	t_axis	id;

	id = (t_axis){0};
	while (id.y < master.rows)
	{
		id.x = 0;
		while (id.x < master.cols)
		{
			ft_printf("%p ", master.mcolor[id.y][id.x]);
			id.x++;
		}
		ft_printf("\n");
		id.y++;
	}
	ft_printf("\n");
}*/

int	main(int argc, char **argv)
{
	t_master	master;
	int			color;
	int			color2;
	t_axis		org;
	t_axis		dest;
	int			x;
	int			y;

	init_check(argc, argv, &master);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, 
			&master.img.line_length, &master.img.endian);
	y = 0;
	color = 0x0000FFFF;
	color2 = 0x00FF0000;
//	matrix_print(master);
//	if (master.color)
//		mcolor_print(master);
	while(y < master.rows)
	{
		x = 0;
		while(x < master.cols)
		{
			org = (t_axis){0};
			projection(&master, x, y, &org);
			org.color = color;
			dest.color = color2;
			if (x + 1 < master.cols)
			{
				dest = (t_axis){0};
				projection(&master, x + 1, y, &dest);
//				if (dest.x < 0 || dest.x > WIDTH || dest.y > HEIGHT || dest.y < 0)
//					continue ;
				bresanham(&master.img, org, dest);
			}
			if (y + 1 < master.rows)
			{
				dest = (t_axis){0};
				projection(&master, x, y + 1, &dest);
//				if (dest.x < 0 || dest.x > WIDTH || dest.y > HEIGHT || dest.y < 0)
//					continue ;
				bresanham(&master.img, org, dest);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(master.mlx.mlx, master.mlx.window, master.img.img, 0, 0);
	mlx_hook(master.mlx.window, 2, 1L<<0, key_map, &master.mlx);
	mlx_hook(master.mlx.window, 17, 1L<<17, close_program, &master.mlx);
	mlx_loop(master.mlx.mlx);	
	return (0);
}
