/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:48:42 by buehara           #+#    #+#             */
/*   Updated: 2025/12/21 20:18:40 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	select_projection(t_master *master, int view)
{
	master->camera.projection = view;
	mlx_destroy_image(master->mlx.mlx, master->img.img);
	ft_fdf(master);
}

void	reset_rotate(t_master *master)
{
	master->camera.angle_x = 0;
	master->camera.angle_y = 0;
	master->camera.angle_z = 0;
}

void	projection_offset(t_camera *camera)
{
	camera->offset_x = WIDTH / 2 + camera->x_add;
	camera->offset_y = HEIGHT / 2 + camera->y_add;
}

void	delta_update(t_master *master, t_delta *delta, int x, int y)
{
	delta->x = (x - (master->cols - 1) / 2) * master->camera.zoom;
	delta->y = (y - (master->rows - 1) / 2) * master->camera.zoom;
}
