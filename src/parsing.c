/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:14:41 by buehara           #+#    #+#             */
/*   Updated: 2025/12/15 21:13:00 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	count_num(t_master *master, int fd)
{
	int		cols;
	char	*buffer;

	buffer = NULL;
	while (!buffer)
	{
		cols = 0;
		buffer = get_buffer(fd);
		if (!buffer)
			break ;
		buffer_check(buffer, &cols, &master->color);
		free(buffer); 
		buffer = NULL; 
		if (master->cols == 0)
			master->cols = cols;
		if (master->cols != cols)
		{
			ft_putstr_fd("File Error: Wrong Format Map\n", 2);
			close(fd);
			exit (ERROR);
		}
		master->rows++; 
	}
	return (TRUE); 
}

void	ft_split_free(char **split)
{
	int	idx;

	idx = 0;
	while (split[idx] != NULL)
	{
		free(split[idx]);
		idx++;
	}
	free(split);
}
	
void	values_checker(char *buf, t_master *master, t_axis *id)
{
	char	**split;
	int		idx;
	int		hex;

	idx = 0;
	hex = 0;
	split = ft_split(buf, ' ');
	if (!split)
		return ;
	while (idx < master->cols)
	{
		master->matrix[id->y][id->x] = ft_atoi(split[idx]);
		if (master->color && ft_strchr(split[idx], ','))
		{
			hex = ft_atoi_hex(ft_strchr(split[idx], ',') + 1, HEX);
			master->mcolor[id->y][id->x] = hex;
		}
		else if (master->color)
			master->mcolor[id->y][id->x] = DEFCOLOR;
		idx++;
		id->x++;
	}
	ft_split_free(split);
}

int	ft_atoi_hex(char *nbr, int base)
{
	long int	hex;
	int			idx;

	hex = 0;
	idx = 0;
	if (nbr[0] == '0' && (nbr[1] == 'x' || nbr[1] == 'X'))
		idx += 2;
	while (nbr[idx])
	{
		if (ft_isdigit(nbr[idx]))
			hex = hex * base + (nbr[idx] - '0');
		else if (nbr[idx] >= 'a' && nbr[idx] <= 'f') 
			hex = hex * base + (nbr[idx] - 'a' + 10);
		else if (nbr[idx] >= 'A' && nbr[idx] <= 'F')
			hex = hex * base + (nbr[idx] - 'A' + 10);
		else
			break ;
		idx++;
	}
	return (hex);
}
