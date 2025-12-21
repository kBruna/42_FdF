/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresanham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:33:47 by buehara           #+#    #+#             */
/*   Updated: 2025/12/20 20:52:15 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ishigher(int org, int dest)
{
	if (org < dest)
		return (1);
	return (-1);
}

void	ft_void_swap(void *var1, void *var2, size_t size)
{
	void	*temp;

	temp = ft_calloc(size, 1);
	ft_memcpy(temp, var1, size);
	ft_memcpy(var1, var2, size);
	ft_memcpy(var2, temp, size);
	free(temp);
}

void	map_size(t_master *master, t_point *max, t_point *min, t_axis *map)
{
	t_point	id;

	id.y = 0;
	master->camera.zoom = 1;
	while (id.y + 1 < master->rows)
	{
		id.x = 0;
		while (id.x + 1 < master->cols)
		{
			*map = (t_axis){0};
			projection(master, id.x, id.y, map);
			if (map->y < min->y)
				min->y = map->y;
			if (map->y > max->y)
				max->y = map->y;
			if (map->x > max->x)
				max->x = map->x;
			if (map->x < min->x)
				min->x = map->x;
			id.x++;
		}
		id.y++;
	}
	map->x = max->x - min->x;
	map->y = max->y - min->y;
}

void	zoom_init(t_master *master)
{
	double	w_size;
	double	h_size;
	t_axis	map;

	if (!master->rows || !master->cols)
		return ;
	master->camera.offset_x = WIDTH;
	master->camera.offset_y = HEIGHT;
	map_size(master, &master->max, &master->min, &map);
	h_size = floor((WIDTH * 0.7) / map.x);
	w_size = floor((HEIGHT * 0.7) / map.y);
	if (h_size > w_size)
		master->camera.zoom *= w_size;
	else
		master->camera.zoom *= h_size;
}
