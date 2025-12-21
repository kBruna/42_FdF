/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:14:17 by buehara           #+#    #+#             */
/*   Updated: 2025/12/21 20:22:58 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	main(int argc, char **argv)
{
	t_master	master;

	init_check(argc, argv, &master);
	ft_fdf(&master);
	fdf_hook(&master);
	mlx_put_image_to_window(master.mlx.mlx,
		master.mlx.window, master.img.img, 0, 0);
	mlx_loop(master.mlx.mlx);
	return (0);
}
