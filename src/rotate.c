/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:21:25 by buehara           #+#    #+#             */
/*   Updated: 2025/12/21 20:27:37 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	rotate_angle(double *y, double *x, double *z, t_camera camera)
{
	rotate_x_z(y, z, camera.angle_x);
	rotate_x_z(x, z, camera.angle_y);
	rotate_y(x, y, camera.angle_z);
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
