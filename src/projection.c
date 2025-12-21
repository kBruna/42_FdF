/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:19:56 by buehara           #+#    #+#             */
/*   Updated: 2025/12/21 20:22:33 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	project_iso(t_master *master, int x, int y, t_axis *dest)
{
	t_delta		delta;
	double		z_zoom;
	double		temp_dx;
	long double	depth;
	long double	brightness;

	projection_offset(&master->camera);
	z_zoom = master->camera.zoom * 0.25;
	dest->z = master->matrix[y][x] * z_zoom;
	delta_update(master, &delta, x, y);
	rotate_angle(&delta.y, &delta.x, &dest->z, master->camera);
	temp_dx = delta.x;
	delta.x = (temp_dx - delta.y) * cos(ANGLE);
	delta.y = (temp_dx + delta.y) * sin(ANGLE) - dest->z;
	dest->x = (int)round(delta.x + master->camera.offset_x);
	dest->y = (int)round(delta.y + master->camera.offset_y);
	depth = (float)(x + y) / (float)(master->cols + master->rows - 2);
	brightness = (depth * 0.8) + 0.2;
	if (master->color)
		dest->color = depth_color(master->mcolor[y][x], brightness);
	else
		dest->color = depth_color(DEFCOLOR, brightness);
}

void	project_top(t_master *master, int x, int y, t_axis *dest)
{
	t_delta		delta;
	long double	depth;
	long double	brightness;

	projection_offset(&master->camera);
	delta_update(master, &delta, x, y);
	dest->x = (int)round(delta.x + master->camera.offset_x);
	dest->y = (int)round(delta.y + master->camera.offset_y);
	depth = (float)master->matrix[y][x] / (master->max.z + master->min.z);
	brightness = (depth * 0.7) + 0.3;
	if (master->color)
		dest->color = depth_color(master->mcolor[y][x], brightness);
	else
		dest->color = depth_color(DEFCOLOR, ON);
}

void	project_x(t_master *master, int x, int y, t_axis *dest)
{
	t_delta		delta;
	double		z_zoom;
	long double	depth;
	long double	brightness;

	projection_offset(&master->camera);
	z_zoom = master->camera.zoom * 0.5;
	delta_update(master, &delta, x, y);
	dest->z = (master->matrix[y][x] - master->max.z / 2) * z_zoom;
	dest->y = (int)round(-dest->z + master->camera.offset_y);
	dest->x = (int)round(delta.x + master->camera.offset_x);
	depth = (float)y / (float)(master->rows - 1);
	brightness = (depth * 0.8) + 0.2;
	if (master->color)
		dest->color = depth_color(master->mcolor[y][x], brightness);
	else
		dest->color = depth_color(DEFCOLOR, brightness);
}

void	project_y(t_master *master, int x, int y, t_axis *dest)
{
	t_delta		delta;
	double		z_zoom;
	long double	depth;
	long double	brightness;

	projection_offset(&master->camera);
	z_zoom = master->camera.zoom * 0.5;
	delta_update(master, &delta, x, y);
	dest->z = (master->matrix[y][x] - master->max.z / 2) * z_zoom;
	dest->x = (int)round(delta.y + master->camera.offset_x);
	dest->y = (int)round(-dest->z + master->camera.offset_y);
	depth = (float)x / (float)(master->cols - 1);
	brightness = (depth * 0.8) + 0.2;
	if (master->color)
		dest->color = depth_color(master->mcolor[y][x], brightness);
	else
		dest->color = depth_color(DEFCOLOR, brightness);
}

void	projection(t_master *master, int x, int y, t_axis *dest)
{
	if (master->camera.projection == ISO)
		project_iso(master, x, y, dest);
	else if (master->camera.projection == TOP_VIEW)
		project_top(master, x, y, dest);
	else if (master->camera.projection == X_VIEW)
		project_x(master, x, y, dest);
	else if (master->camera.projection == Y_VIEW)
		project_y(master, x, y, dest);
}
