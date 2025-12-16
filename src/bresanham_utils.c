/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresanham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:33:47 by buehara           #+#    #+#             */
/*   Updated: 2025/12/15 12:09:23 by buehara          ###   ########.fr       */
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

void	zoom_init(t_master *master)
{
	double	w_size;
	double	h_size;

	if (!master->rows || !master->cols)
		return ;
	h_size = HEIGHT / master->rows;
	w_size = WIDTH / master->cols;
	if (h_size > w_size)
		master->zoom = w_size / 1.5;
	else
		master->zoom = h_size / 1.5;
}
