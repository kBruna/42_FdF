/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:21:25 by buehara           #+#    #+#             */
/*   Updated: 2025/12/22 12:25:33 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	rotate_angle(double *y, double *x, double *z, t_camera camera)
{
	rotate_x_z(y, z, camera.angle_x);
	rotate_x_z(x, z, camera.angle_z);
	rotate_y(x, y, camera.angle_y);
}

void	rotate_x_z(double *y, double *z, float angle)
{
	double	temp_y;

	temp_y = *y;
	*y = temp_y * cos(angle) - (*z) * sin(angle);
	*z = temp_y * sin(angle) + (*z) * cos(angle);
}

void	rotate_y(double *x, double *z, float angle)
{
	double	temp_x;

	temp_x = *x;
	*x = temp_x * cos(angle) + (*z) * sin(angle);
	*z = -temp_x * sin(angle) + (*z) * cos(angle);
}

int	rotate_animate(t_master *master)
{
	if (master->camera.rotate_auto)
	{
		master->camera.angle_y -= 0.001;
		if (master->camera.angle_y <= -2 * M_PI)
			master->camera.angle_y = 0;
		mlx_destroy_image(master->mlx.mlx, master->img.img);
		ft_fdf(master);
	}
	return (0);
}
