/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:14:17 by buehara           #+#    #+#             */
/*   Updated: 2025/12/13 17:25:28 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

void	zoom_init(t_master *master)
{
	int	w_size;
	int h_size;

	h_size = HEIGHT / (master->rows + master->cols);
	w_size = WIDTH / (master->cols + master->rows);
	if (h_size > w_size)
		master->zoom = w_size / 2;
	else
		master->zoom = h_size / 2;
}

void	projection(t_master *master, int x, int y, t_axis *dest)
{
	double	dx;
	double	dy;
	double	z;
	double	z_zoom;

	z_zoom = 1;
	z = master->matrix[y][x] * z_zoom;
	dx = x - (master->cols - 1)/ 2;
	dy = y - (master->rows - 1)/ 2;
	dx *= master->zoom;
	dy *= master->zoom;
	dx = (dx - dy) * cos(ANGLE);
	dy = (dx + dy) * sin(ANGLE) - z;
	dx += WIDTH / 2;
	dy += HEIGHT / 2;
	dest->x = (int)round(dx);
	dest->y = (int)round(dy);
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
		if (org.x > 0 && org.x < WIDTH && org.y > 0 && org.y < HEIGHT)
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

int	init_check(int argc, char **argv, t_master *master)
{
	int			fd;

	fd = open_map(argc, argv);
	if (fd == -1)
		return (FALSE);
	if (!matrix_init(master, fd))
		return (FALSE);
	fd = open_map(argc, argv);
	if (fd == -1)
	{
		matrix_error(master->mcolor, master);
		return (FALSE);
	}
	if (!matrix_fill(fd, master))
		return (FALSE);
	if(!ft_mlx_init(master))
		return (FALSE);
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

	if (!init_check(argc, argv, &master))
		return (FALSE);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, 
			&master.img.line_length, &master.img.endian);
	y = 0;
	color = 0x0000FFFF;
	color2 = 0x00FF0000;
	while(y < master.rows)
	{
		x = 0;
		while(x < master.cols)
		{
			projection(&master, x, y, &org);
			org.color = color;
			dest.color = color2;
			if (x + 1 < master.cols)
			{
				dest = (t_axis){0};
				projection(&master, x + 1, y, &dest);
				if (dest.x < 0 || dest.x > WIDTH || dest.y > HEIGHT || dest.y < 0)
					continue ;
				bresanham(&master.img, org, dest);
			}
			if (y + 1 < master.rows)
			{
				dest = (t_axis){0};
				projection(&master, x, y + 1, &dest);
				if (dest.x < 0 || dest.x > WIDTH || dest.y > HEIGHT || dest.y < 0)
					continue ;
				bresanham(&master.img, org, dest);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(master.mlx.mlx, master.mlx.window, master.img.img, 0, 0);
	mlx_hook(master.mlx.window, 2, 1L<<0, key_map, &master.mlx);
	mlx_hook(master.mlx.window, 17, 1L<<17, close_program, &master.mlx);
	mlx_loop(master.mlx.mlx);	
	return (0);
}
