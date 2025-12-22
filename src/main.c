/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:14:17 by buehara           #+#    #+#             */
/*   Updated: 2025/12/22 12:25:47 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	main(int argc, char **argv)
{
	t_master	master;

	init_check(argc, argv, &master);
	fdf_hook(&master);
	mlx_loop_hook(master.mlx.mlx, rotate_animate, &master);
	ft_fdf(&master);
	mlx_loop(master.mlx.mlx);
	return (0);
}
