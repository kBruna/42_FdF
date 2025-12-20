/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 09:56:26 by buehara           #+#    #+#             */
/*   Updated: 2025/12/20 16:35:42 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	matrix_error(int **color, t_master *master)
{
	matrix_free(color, master->rows);
	matrix_free(master->matrix, master->rows);
	exit (ERROR);
}

void	matrix_init(t_master *master, int fd)
{
	int	**color;

	master->cols = 0;
	master->rows = 0;
	master->color = OFF;
	master->zoom = 0;
	master->mcolor = NULL;
	master->projection = ISO;
	master->max.x = MIN_INT;
	master->max.y = MIN_INT;
	master->max.z = MIN_INT;
	master->min.x = MAX_INT;
	master->min.y = MAX_INT;
	master->min.z = MAX_INT;
	count_num(master, fd);
	color = matrix_double(master);
	if (!master->matrix)
	{
		matrix_free(master->matrix, master->rows);
		exit (ERROR);
	}
	if (master->color && !color)
		matrix_error(color, master);
	master->mcolor = color;
}

int	matrix_fill(int fd, t_master *master)
{
	t_axis	id;
	char	*buf;

	id.y = 0;
	while (id.y < master->rows)
	{
		buf = get_buffer(fd);
		if (!buf)
		{
			matrix_error(master->mcolor, master);
			return (FALSE);
		}
		id.x = 0;
		while (id.x < master->cols)
			values_checker(buf, master, &id);
		free(buf);
		id.y++;
	}
	close(fd);
	zoom_init(master);
	return (TRUE);
}
