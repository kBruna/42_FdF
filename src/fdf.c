/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:24:43 by buehara           #+#    #+#             */
/*   Updated: 2025/12/20 14:12:28 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_fdf(t_master *master)
{
	t_point	id;

	master->img.img = mlx_new_image(master->mlx.mlx, WIDTH, HEIGHT);
	if (!master->img.img)
	{
		clean_program(master, OFF);
		return ;
	}
	master->img.addr = mlx_get_data_addr(master->img.img, &master->img.bpp,
			&master->img.line_length, &master->img.endian);
	master->img.steep = 0;
	id.y = 0;
	while (id.y < master->rows)
	{
		id.x = 0;
		while (id.x < master->cols)
		{
			bres_call(master, id);
			id.x++;
		}
		id.y++;
	}
	mlx_put_image_to_window(master->mlx.mlx,
		master->mlx.window, master->img.img, 0, 0);
}

void	bres_call(t_master *master, t_point id)
{
	t_axis	org;
	t_axis	dest;

	org = (t_axis){0};
	dest = (t_axis){0};
	projection(master, id.x, id.y, &org);
	if (id.x + 1 < master->cols)
	{
		projection(master, id.x + 1, id.y, &dest);
		bresanham(&master->img, org, dest);
	}
	if (id.y + 1 < master->rows)
	{
		projection(master, id.x, id.y + 1, &dest);
		bresanham(&master->img, org, dest);
	}
	if (master->color && id.x + 1 < master->cols && id.y + 1 < master->rows)
	{
		projection(master, id.x + 1, id.y + 1, &dest);
		bresanham(&master->img, org, dest);
	}
}
