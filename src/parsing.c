/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:14:41 by buehara           #+#    #+#             */
/*   Updated: 2025/12/13 10:26:08 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	*get_buffer(int fd)
{
	char	*buffer;

	buffer = get_next_line(fd);
	if (buffer == NULL)
	{
		free(buffer);
		close(fd);
	}
	return (buffer);
}

void	buffer_check(char *buffer, int *cols, int *color)
{
	int		idx;
	char	**split;

	idx = 0;
	split = ft_split(buffer, ' ');
	while (split[idx] != NULL)
	{
		if (ft_strchr(split[idx], ','))
			(*color) = 1;
		idx++;
	}
	(*cols) = idx;
	while (idx > 0)
	{
		idx--;
		free(split[idx]);
	}
	free(split);
}
	
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
		else if (master->cols != cols)
		{
			ft_putstr_fd("Error: Wrong Map Format\n", 2);
			close(fd);
			return (FALSE);
		}	
		master->rows++; 
	}
	return (TRUE); 
}

int	ft_atoi_hex(char *nbr, int base)
{
	long int	hex;

	hex = 0;
	if (nbr[0] == '0' && (nbr[1] == 'x' || nbr[1] == 'X'))
		*nbr += 2;
	while (*nbr)
	{
		if (ft_isdigit(*nbr))
			hex = hex * base + (*nbr - '0');
		else if (*nbr >= 'a' && *nbr <= 'f') 
			hex = hex * base + (*nbr - 'a' + 10);
		else if (*nbr >= 'A' && *nbr <= 'F')
			hex = hex * base + (*nbr - 'A' + 10);
		else
			break ;
		*nbr += 1;
	}
	return (hex);
}

void	values_checker(char *buf, t_master *master, int *index, t_axis *id)
{
	if (ft_isdigit(buf[*index]) || buf[*index] == '-' || buf[*index] == '+')
		master->matrix[id->y][id->x] = ft_atoi(&buf[*index]);
	while (ft_isdigit(buf[*index]))
		(*index)++;	
	if (master->color && buf[*index] == ',')
	{
		(*index)++;	
		master->mcolor[id->y][id->x] = ft_atoi_hex(buf, HEX);
	}
	while (ft_isspace(buf[*index]))
		(*index)++;	
	id->x++;
}
