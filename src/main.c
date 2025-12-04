/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:14:17 by buehara           #+#    #+#             */
/*   Updated: 2025/12/03 22:31:37 by buehara          ###   ########.fr       */
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

void	bresanham(t_data *view, t_axis org, t_axis dest)
{
	double	bress;
	int		dx;
	int		dy;
	t_axis	diff;

	dx = abs(dest.x - org.x);
	dy = abs(dest.y - org.y);
	diff.x = ishigher(org.x, dest.x);
	diff.y = ishigher(org.y, dest.y);
	if (dy > dx)
	{
		ft_void_swap(&dx, &dy, sizeof(int));
		ft_void_swap(&org.x, &org.y, sizeof(int));
		ft_void_swap(&dest.x, &dest.y, sizeof(int));
		ft_void_swap(&diff.x, &diff.y, sizeof(int));
	}
	bress = 2 * dy - dx;
	while (org.x != dest.x || org.y != dest.y)
	{
		pixel_put(view, org.x, org.y, org.color);
		if (bress < 0)
		{
			bres_util(&org.x, &org.y, bress, diff);
			bress += 2 * dy;
		}
		else
		{
			bres_util(&org.x, &org.y, bress, diff);
			bress += 2 * dy - 2 * dx;
		}
	}
}

int	close_program(t_master *master)
{
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

int	main(void)
{
	t_master	master;
	int			color;
	int			color2;
	t_axis		point;
	t_axis		dest;
	int			x = 3;
	int			y = 2;
	int 		matrix[3][2] = {
				{0, 0},
				{0, 1},
				{0, 0}
				};
	int			width = 2;
	int			height = 3;
	double		dx;
	double		dy;
	
	if(!ft_mlx_init(&master))
		return (FALSE);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, 
			&master.img.line_length, &master.img.endian);
	color = 0x0000FFFF;
	color2 = 0x00FF0000;
/*	point.x = 0;
	bress_right(&master.img, &p2, dest, color2);*/
	x = 0;
	while(x <= height)
	{
		y = 0;	
		while(y <= width)
		{
			// Projection Code
			dx = (x - y) * cos(0.523599);
			dy = (y + x) * sin(0.523599) + matrix[x][y];
			dx *= 10;
			dy *= 10;
			dx += 500 / 2; // * ZOOM latter --- WIDTH / 2
			dy += 500 / 2; // same ^ --- HEIGHT / 2 
			//End Projection Code;
			point.x = round(dx);
			point.y = round(dy);
			point.color = color;
			dest.color = color2;
			dx = ((x+1) - y) * cos(0.523599);
			dy = ((x+1) + y) * sin(0.523599) + matrix[x][y];
			dx *= 10;
			dy *= 10;
			dx += 500 / 2; // * ZOOM latter --- WIDTH / 2
			dy += 500 / 2; // same ^ --- HEIGHT / 2 
			dest.x = dx;
			dest.y = dy;
			bresanham(&master.img, point, dest);
			dx = (x - (y + 1)) * cos(0.523599);
			dy = (x + (y + 1)) * sin(0.523599) + matrix[x][y];
			dx *= 10;
			dy *= 10;
			dx += 500 / 2; // * ZOOM latter --- WIDTH / 2
			dy += 500 / 2; // same ^ --- HEIGHT / 2 
			dest.x = dx;
			dest.y = dy;
	//		dest.y = round(dy) + 10;
			bresanham(&master.img, point, dest);
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
