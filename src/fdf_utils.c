/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:45:35 by buehara           #+#    #+#             */
/*   Updated: 2025/12/17 14:50:07 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	open_map(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Wrong number of parameters used\n", 2);
		exit (ERROR);
	}
	fd = open(argv[argc - 1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error: Failed to open map");
		exit (ERROR);
	}
	return (fd);
}

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
	if (!ft_mlx_init(master))
	{
		perror("Error Initializing MLX Lib");
		exit (ERROR);
	}
}

int	close_program(t_master *master)
{
	int	cols;

	cols = 0;
	matrix_free(master->mcolor, master->rows);
	matrix_free(master->matrix, master->rows);
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	mlx_destroy_window(master->mlx.mlx, master->mlx.window);
	mlx_destroy_display(master->mlx.mlx);
	free(master->mlx.mlx);
	exit(0);
}
