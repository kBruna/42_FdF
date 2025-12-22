/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_keycodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:18:33 by buehara           #+#    #+#             */
/*   Updated: 2025/12/22 12:21:53 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	fdf_hook(t_master *master)
{
	mlx_hook(master->mlx.window, 2, 1L << 0, key_map, &master->mlx);
	mlx_hook(master->mlx.window, 17, 1L << 17, close_program, &master->mlx);
}

int	key_map(int keycode, t_master *master)
{
	if (keycode == XK_Escape)
		close_program(master);
	else if (keycode == XK_1)
		select_projection(master, TOP_VIEW);
	else if (keycode == XK_2)
		select_projection(master, X_VIEW);
	else if (keycode == XK_3)
		select_projection(master, Y_VIEW);
	else if (keycode == XK_0)
		select_projection(master, ISO);
	else if (keycode == XK_i || keycode == XK_o)
		zoom_projection(master, keycode);
	else if (keycode == XK_w || keycode == XK_a
		|| keycode == XK_d || keycode == XK_s)
		translate(master, keycode);
	else if (keycode == XK_Up || keycode == XK_Down || keycode == XK_e
		|| keycode == XK_Right || keycode == XK_Left || keycode == XK_q
		|| keycode == XK_r)
		rotate(master, keycode);
	else if (keycode == XK_k)
		master->camera.rotate_auto = !master->camera.rotate_auto;
	return (0);
}

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
		master->camera.angle_z += 0.1;
	else if (keycode == XK_Left)
		master->camera.angle_z -= 0.1;
	if (keycode == XK_q)
		master->camera.angle_y += 0.1;
	else if (keycode == XK_e)
		master->camera.angle_y -= 0.1;
	if (keycode == XK_r)
		reset_rotate(master);
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	ft_fdf(master);
}
