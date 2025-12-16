/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:24:43 by buehara           #+#    #+#             */
/*   Updated: 2025/12/16 20:31:42 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_fdf(t_master *master)
{
	t_point	id;

	id.y = 0;
	while(id.y < master->rows)
	{
		id.x = 0;
		while(id.x < master->cols)
		{
			bres_call(master, id);
			id.x++;
		}
		id.y++;
	}
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
