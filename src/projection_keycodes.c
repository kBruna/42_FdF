/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_keycodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:18:33 by buehara           #+#    #+#             */
/*   Updated: 2025/12/21 19:19:04 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	zoom_projection(t_master *master, int keycode)
{
	float	add_zoom;

	if (master->rows > 20 && master->cols > 20)
		add_zoom = 0.5;
	else
		add_zoom = 2;
	if (keycode == XK_o && master->camera.zoom > 1)
		master->camera.zoom -= add_zoom;
	else if (keycode == XK_i)
		master->camera.zoom += add_zoom;
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	ft_fdf(master);
}

void	translate(t_master *master, int keycode)
{
	if (keycode == XK_w)
		master->camera.y_add -= 2;
	else if (keycode == XK_s)
		master->camera.y_add += 2;
	if (keycode == XK_d)
		master->camera.x_add += 2;
	else if (keycode == XK_a)
		master->camera.x_add -= 2;
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	ft_fdf(master);
}

void	rotate(t_master *master, int keycode)
{
	if (keycode == XK_Up)
		master->camera.angle_x += 0.1;
	else if (keycode == XK_Down)
		master->camera.angle_x -= 0.1;
	if (keycode == XK_Right)
		master->camera.angle_y += 0.1;
	else if (keycode == XK_Left)
		master->camera.angle_y -= 0.1;
	if (keycode == XK_q)
		master->camera.angle_z += 0.1;
	else if (keycode == XK_e)
		master->camera.angle_z -= 0.1;
	if (keycode == XK_r)
		reset_rotate(master);
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	ft_fdf(master);
}
