/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 09:56:26 by buehara           #+#    #+#             */
/*   Updated: 2025/12/13 11:40:01 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	matrix_error(int **color, t_master *master)
{
	matrix_free(color, master->rows);
	matrix_free(master->matrix, master->rows);
	return ;
}

int	matrix_init(t_master *master, int fd)
{
	int	**color;

	master->cols = 0;
	master->rows = 0;
	master->color = 0;
	master->zoom = 0;
	master->mcolor = NULL;
	if (!count_num(master, fd))
		return (FALSE);
	color = matrix_double(master);
	if (!master->matrix)
	{
		matrix_free(master->matrix, master->rows);
		return (FALSE);
	}
	if (master->color && !color)
	{
		matrix_error(color, master);
		return (FALSE);
	}
	master->mcolor = color;
	return (TRUE);
}

int	matrix_fill(int fd, t_master *master)
{
	t_axis 	id;
	char	*buf;
	int		index;

	id.y = 0;
	while (id.y < master->rows)
	{
		index = 0;
		buf = get_buffer(fd);
		if (!buf)
		{
			matrix_error(master->mcolor, master);
			return (FALSE);
		}
		id.x = 0;
		while (id.x < master->cols)
			values_checker(buf, master, &index, &id);
		free(buf);
		id.y++;
	}
	close(fd);
	zoom_init(master);
	return (TRUE);
}


