/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:14:17 by buehara           #+#    #+#             */
/*   Updated: 2025/12/05 20:33:50 by buehara          ###   ########.fr       */
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
	if (*buffer == NULL)
	{
		free(buffer);
		close(fd);
		return (FALSE);
	}
	return (buffer);
}
	
int	count_num(t_master *master)
{
	int	idx;
	char	*buffer;

	buffer = NULL;
	while (buffer[0] != '\n')
	{
		*buffer = get_buffer(fd);
		if (!buffer)
			return (FALSE);
		idx = 0;
		while(*buffer[idx] != '\0')
		{
			if (ft_isdigit(*buffer[idx++]))
				master->cols++;
			if (ft_isspace(*buffer[idx]))
				idx++;
			if (*buffer[idx++] == ',')
				while (!ft_isspace(*buffer[idx])
					idx++;
		}
		free(buffer);
		master->rows++;
	}
	return (TRUE);
}

int	open_map(int argc, char **argv, char **buffer)
{
	int	fd;

	if (argc != 2)
		return (FALSE);
	fd = open(argv[argc - 1], O_RDONLY);
	if (fd == -1)
		return (FALSE);
}

void	matrix_fill(int	fd)
{
	char	*buffer;

	master.matrix = (int **)malloc(master.rows * sizeof(int *));
	if (master.matrix == NULL)
		return ;
	x = 0;
	buffer = get_buffer(fd);
	if (!buffer)
		return ;
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
			y++; // ADD COLORS GET
		}
		x++;
	}
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
	int			width = 5;
	int			height = 5;

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
	if (!open_map(argc, argv, &buffer)) //Opening Map
		return (FALSE);
	master.cols = 0;
	master.rows = 0;
	if (!count_num(buffer, &master)) //Populating Master Matrix Numbers
		return (FALSE);
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
	} // END FUNCTION
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
