/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresanham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:33:47 by buehara           #+#    #+#             */
/*   Updated: 2025/12/17 21:26:12 by buehara          ###   ########.fr       */
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

int	range(t_master *master)
{
	t_point	id;
	int		max;
	int		min;

	id = (t_point){0};
	max = 0;
	min = 0;
	while (id.y + 1 < master->rows)
	{
		id.x = 0;
		while (id.x + 1 < master->cols)
		{
			if (max < master->matrix[id.y][id.x])
				max = master->matrix[id.y][id.x];
			if (min > master->matrix[id.y][id.x])
				min = master->matrix[id.y][id.x];
			id.x++;
		}
		id.y++;
	}
	return(max - min);
}

void	zoom_init(t_master *master)
{
	double	w_size;
	double	h_size;
	int		number;
	int		denominator;

	if (!master->rows || !master->cols)
		return ;
	number = range(master);
	denominator = (master->rows + master->cols) / 2;
	h_size = HEIGHT / master->rows;
	w_size = WIDTH / master->cols;
	if (h_size > w_size)
		master->zoom = w_size / 1.5;
	else
		master->zoom = h_size / 1.5;
	if (number > 50 && number * master->zoom > (HEIGHT / 2))
		master->zoom = (int)ceil(number / denominator);
}
// TODO: I DUNNO ANYMORE
