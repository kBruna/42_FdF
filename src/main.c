/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:14:17 by buehara           #+#    #+#             */
/*   Updated: 2025/11/28 21:25:16 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	bress_left(t_data *view, t_axis *org, t_axis dest, int color)
{
	int		bress;

	bress = 2 * abs(dest.x - org->x) - abs(dest.y - org->y);
	while (org->y <= dest.y)
	{
		pixel_put(view, dest.x * cos(0.523599) + org->displace, dest.y * sin(0.523599) + org->displace, color);
		dest.y--;
		if (bress <= 0)
			bress += 2 * abs(dest.x - org->x);
		else
		{
			bress +=  2 * abs(dest.x - org->x) - abs(dest.y - org->y);
			dest.x++;
		}
	}
}

void	bress_right(t_data *view, t_axis *org, t_axis dest, int color)
{
	int		bress;

	bress = 2 * (dest.x - org->x) - (dest.y - org->y);
	while (org->x <= dest.x)
	{
		pixel_put(view, org->x * cos(0.523599) + org->displace, org->y * sin(0.523599) + org->displace, color);
		org->x++;
		if (bress < 0)
			bress += 2 * (dest.x - org->x);
		else
		{
			bress += 2 * (dest.x - org->x) - (dest.y - org->y);
			org->y++;
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

int	main()
{
	t_master	master;
	int			color;
	int			color2;
//	t_axis		dest2;
	t_axis		point;
//	t_axis		p2;
	t_axis		dest;
//	int 		matrix[2][2] = {
//				{0, 0},
//				{0, 0}
//				};
	int			totalx = 2;
	int			totaly = 2;
//	float		ang;
	
	if(!ft_mlx_init(&master))
		return (FALSE);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, 
			&master.img.line_length, &master.img.endian);
	color = 0x0000FFFF;
	color2 = 0x00FF0000;
/*	point.x = 0;
	point.y = 0;
	point.displace = 100;
	p2.x = 30;
	p2.y = 10;
	p2.displace = 100;
	dest.x = 80;
	dest.y = 60;
	dest2.x = 50;
	dest2.y = 50;
	dest2.displace = 100;
	dest.displace = 100;*/
//	ang = 0.523599;
/*	bress_left(&master.img, &point, dest2, color);
	bress_right(&master.img, &p2, dest, color2);*/
	while(totalx > 0)
	{
		dest.x = totalx * 10;
		dest.y = totaly * 10;
		dest.displace = 20;
		totalx--;
		totaly--;
		point.x = totalx * 10;
		point.y = totaly * 10;
		point.displace = 30;
		totalx--;
		totaly--;
		bress_left(&master.img, &point, dest, color);
		bress_right(&master.img, &point, dest, color2);
//		point.y += 10;
		dest.y += 10;
//		point.x += 10;
		dest.x += 10; 
		point.displace = 15;
		dest.displace = 20;
		bress_left(&master.img, &point, dest, color);
		point.x = 0;
		point.y = 10;
		dest.x = 10;
		dest.y = 20;
		dest.displace = 50;
		point.displace = 100;
		bress_right(&master.img, &point, dest, color2);
	}
	mlx_put_image_to_window(master.mlx.mlx, master.mlx.window, master.img.img, 0, 0);
	mlx_hook(master.mlx.window, 2, 1L<<0, key_map, &master.mlx);
	mlx_hook(master.mlx.window, 17, 1L<<17, close_program, &master.mlx);
	mlx_loop(master.mlx.mlx);	
	return (0);
}
