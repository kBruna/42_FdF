/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 09:50:54 by buehara           #+#    #+#             */
/*   Updated: 2025/12/13 09:56:02 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	matrix_free(int **matrix, int rows)
{
	int	idx;

	if (!matrix)
		return ;
	idx = 0;
	while (idx < rows)
	{
		free(matrix[idx]);
		idx++;
	}
	free(matrix);
}

int	**matrix_make(t_master *master)
{
	int	**matrix;
	int	idx;

	matrix = (int **)ft_calloc(master->rows, sizeof(int *));
	if (!matrix)
		return (NULL);
	idx = 0;
	while (idx < master->rows)
	{
		matrix[idx] = (int *)ft_calloc(master->cols,sizeof(int));
		if (matrix[idx] == NULL)
		{
			while (idx > 0)
			{
				idx--;
				free(matrix[idx]);
			}
			free(matrix);
			return (NULL);
		}
		idx++;
	}
	return (matrix);
}

int	**matrix_double(t_master *master)
{
	int		**color;

	master->matrix = matrix_make(master);
	if (!master->matrix)
		return (NULL);
	color = NULL;
	if (master->color)
	{
		color = matrix_make(master);
		if (!color)
		{
			matrix_free(master->matrix, master->rows);
			return (NULL);
		}
	}
	return (color);
}
