/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:14:17 by buehara           #+#    #+#             */
/*   Updated: 2025/12/10 21:50:11 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	ishigher(int org, int dest)
{
	if (org < dest)
		return (1);
	return (-1);
}

void	bres_util(int *org_x, int *org_y, double bress, t_axis diff)
{
	*org_x += diff.x;
	if (bress >= 0)
		*org_y += diff.y;
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

void	swap_vars(t_axis *cal, t_axis *org, t_axis *dest, t_axis *diff)
{
	ft_void_swap(&cal->x, &cal->y, sizeof(int));
	ft_void_swap(&org->x, &org->y, sizeof(int));
	ft_void_swap(&dest->x, &dest->y, sizeof(int));
	ft_void_swap(&diff->x, &diff->y, sizeof(int));
}

void	bresanham(t_data *view, t_axis org, t_axis dest)
{
	double	bress;
	t_axis	cal;
	t_axis	diff;

	cal.x = abs(dest.x - org.x);
	cal.y = abs(dest.y - org.y);
	diff.x = ishigher(org.x, dest.x);
	diff.y = ishigher(org.y, dest.y);
	if (cal.y > cal.x)
		swap_vars(&cal, &org, &dest, &diff);
	bress = 2 * cal.y - cal.x;
	while (org.x != dest.x || org.y != dest.y)
	{
		pixel_put(view, org.x, org.y, org.color);
		if (bress < 0)
		{
			bres_util(&org.x, &org.y, bress, diff);
			bress += 2 * cal.y;
		}
		else
		{
			bres_util(&org.x, &org.y, bress, diff);
			bress += 2 * cal.y - 2 * cal.x;
		}
	}
}

int	close_program(t_master *master)
{
	int	cols;

	cols = 0;
	while(master->cols > cols)
	{
		free(master->matrix[cols]);
		cols++;
	}
	free(master->matrix);
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	mlx_destroy_window(master->mlx.mlx, master->mlx.window);
	mlx_destroy_display(master->mlx.mlx);
	free(master->mlx.mlx);
	exit(0);
}

int	key_map(int keycode, t_master *master)
{
	if (keycode == XK_Escape)
		close_program(master);
	return (0);
}

int	ft_mlx_init(t_master *master)
{
	master->mlx.mlx = mlx_init();
	if (!master->mlx.mlx)
		return (FALSE);
	master->mlx.window = mlx_new_window(master->mlx.mlx, 500, 500, "FdF");
	if (!master->mlx.window)
	{
		mlx_destroy_display(master->mlx.mlx);
		free(master->mlx.mlx);
		return (FALSE);
	}
	master->img.img = mlx_new_image(master->mlx.mlx, 500, 500);
	if (!master->img.img)
	{
		mlx_destroy_window(master->mlx.mlx, master->mlx.window);
		mlx_destroy_display(master->mlx.mlx);
		free(master->mlx.mlx);
		return (FALSE);
	}
	return (TRUE);
}

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
	int	idx;

	idx = 0;
	while (buffer[idx] != '\0')
	{
		if (ft_isdigit(buffer[idx]))
		{
			(*cols)++;
			idx++;
		}
		if (ft_isspace(buffer[idx]) || buffer[idx] == '-' || buffer[idx] == '+')
			idx++;
		if (buffer[idx] == ',')
		{
			(*color) = 1;
			while (!ft_isspace(buffer[idx]))
				idx++;
		}
	}
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
			return (FALSE);
		buffer_check(buffer, &cols, &master->color);
		free(buffer); 
		buffer = NULL; 
		if (master->cols == 0)
			master->cols = cols;
		else if (master->cols != cols)
		{
			ft_putstr_fd("Error: Wrong Map Format\n", 2); //STDOUT at ERROR FD
			close(fd);
			return (FALSE);
		}	
		master->rows++; 
	}
	return (TRUE); 
}


int	open_map(int argc, char **argv) 
{ 
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Wrong number of parameters used\n", 2);
		return (FALSE);
	}
	fd = open(argv[argc - 1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Failed to open map\n", 2);
		return (FALSE);
	}
	return (fd);
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
	}
	return (hex);
}

void	matrix_error(int **color, t_master *master)
{
	matrix_free(color, master->rows);
	matrix_free(master->matrix, master->rows);
	return ;
}

int	matrix_fill(int fd, t_master *master)
{
	int		**color;
	t_axis 	id;
	char	*buffer;
	int		index;

	color = matrix_double(master);
	if (!master->matrix)
		return (FALSE);
	id.x = 0;
	index = 0;
	while (id.x < master->rows)
	{
		buffer = get_buffer(fd);
		if (!buffer)
		{
			matrix_error(color, master);
			return (FALSE);
		}
		id.y = 0;
		while (id.y < master->cols)
		{
			if (ft_isdigit(buffer[index]))
				master->matrix[id.x][id.y] = ft_atoi(&buffer[index]);
			while (ft_isdigit(buffer[index]))
				index++;	
			if (master->color && buffer[index] == ',')
			{
				index++;
				color[id.x][id.y] = ft_atoi_hex(buffer, HEX);
			}
			while (ft_isspace(buffer[index]))
				index++;
			id.y++;
		}
		free(buffer);
		id.x++;
	}
	close(fd);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_master	master;
	int			color;
	int			color2;
	t_axis		org;
	t_axis		dest;
	int			x;
	int			y;
	//int			width = 5;
	//int			height = 5;
	//int			**mcolor;
	int			fd;

	/*if (argc != 2)
		return (FALSE);
	fd = open(argv[argc - 1], O_RDONLY);
	if (fd == -1)
		return (FALSE);
	buffer = get_next_line(fd);
	if (buffer == NULL)
	{
		close(fd);
		return (FALSE);
	}*/
	fd = open_map(argc, argv);
	if (fd == -1)
		return (FALSE);
	master.cols = 0;
	master.rows = 0;
	master.color = 0;
	if (count_num(&master, fd))
		return (FALSE);
	//if (master.color)
		//mcolor = matrix_double(&master);
	fd = open_map(argc, argv);
	if (fd == -1)
	{
		//matrix_error(mcolor, &master);
		return (FALSE);
	}
	matrix_fill(fd, &master);
	/*
	master.matrix = (int **)malloc(master.rows * sizeof(int *));
	if (master.matrix == NULL)
		return (1);
	x = 0;
	while (x < master.rows)
	{
		master.matrix[x] = (int *)malloc(master.cols * sizeof(int));
		x++;
	}
	x = 0;
	while (x < master.rows)
	{
		y = 0;
		while (y < master.cols)
		{
			master.matrix[x][y] = ft_atoi(buffer);
			y++;
		}
		x++;
	} // END FUNCTION */
	if(!ft_mlx_init(&master))
		return (FALSE);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, 
			&master.img.line_length, &master.img.endian);
	x = 0;
	color = 0x0000FFFF;
	color2 = 0x00FF0000;
	while(x < master.rows)
	{
		y = 0;
		while(y < master.cols)
		{
			projection(master.matrix, x, y, &org);
			org.color = color;
			dest.color = color2;
			if (x + 1 < master.rows)
			{
				projection(master.matrix, x + 1, y, &dest);
				if (dest.x > 500 || dest.y > 500) // CANVAS SIZE
					break ;
				bresanham(&master.img, org, dest);
			}
			if (y + 1 < master.cols)
			{
				projection(master.matrix, x, y + 1, &dest);
				if (dest.x > 500 || dest.y > 500) // CANVAS SIZE
					break ;
				bresanham(&master.img, org, dest);
			}
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(master.mlx.mlx, master.mlx.window, master.img.img, 0, 0);
	mlx_hook(master.mlx.window, 2, 1L<<0, key_map, &master.mlx);
	mlx_hook(master.mlx.window, 17, 1L<<17, close_program, &master.mlx);
	mlx_loop(master.mlx.mlx);	
	return (0);
}

void	projection(int **matrix, int x, int y, t_axis *dest)
{
	double	dx;
	double	dy;
	float	zoom;

	zoom = 20;
	dx = (x - y) * cos(ANGLE);
	dy = (x + y) * sin(ANGLE) * zoom; 
	dy -= matrix[x][y] * zoom;
	dx *= zoom;
	dx += (500 - (5 * 10)) / 2;
	dy += (500 - (4 * 10)) / 2; 
	dest->x = round(dx);
	dest->y = round(dy);
}
