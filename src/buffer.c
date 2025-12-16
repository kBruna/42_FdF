/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:11:18 by buehara           #+#    #+#             */
/*   Updated: 2025/12/15 21:12:42 by buehara          ###   ########.fr       */
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
		if (!ft_strncmp(split[idx], "\n", 1))
			break;
		idx++;
	}
	(*cols) = idx;
	ft_split_free(split);
}


