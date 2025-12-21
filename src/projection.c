/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:19:56 by buehara           #+#    #+#             */
/*   Updated: 2025/12/20 21:32:36 by buehara          ###   ########.fr       */
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

	z_zoom = master->camera.zoom * 0.25;
	dest->z = master->matrix[y][x] * z_zoom;
	delta.x = (x - (master->cols - 1) / 2) * master->camera.zoom;
	delta.y = (y - (master->rows - 1) / 2) * master->camera.zoom;
	temp_dx = delta.x;
	delta.x = (temp_dx - delta.y) * cos(ANGLE);
	delta.y = (temp_dx + delta.y) * sin(ANGLE) - dest->z;
	master->camera.offset_x = WIDTH / 2 + master->camera.x_add;
	master->camera.offset_y = (HEIGHT) * 0.5 + master->camera.y_add;
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
	double		z_zoom;
	long double	depth;
	long double	brightness;

	z_zoom = master->camera.zoom * 0.5;
	delta.x = (x - (master->cols - 1) / 2) * master->camera.zoom;
	delta.y = (y - (master->rows - 1) / 2) * master->camera.zoom;
	depth = (float)master->matrix[y][x] / (float)(master->max.z + master->min.z);
	brightness = (depth * 0.8) + 0.2;
	master->camera.offset_x = WIDTH / 2 + master->camera.x_add;
	master->camera.offset_y = HEIGHT / 2 + master->camera.y_add;
	dest->x = (int)round(delta.x + master->camera.offset_x);
	dest->y = (int)round(delta.y + master->camera.offset_y);
	if (master->color)
		dest->color = depth_color(master->mcolor[y][x], brightness);
	else
		dest->color = depth_color(DEFCOLOR, brightness);
}

void	project_x(t_master *master, int x, int y, t_axis *dest)
{
	t_delta		delta;
	double		z_zoom;
	long double	depth;
	long double brightness;

	z_zoom = master->camera.zoom * 0.5;
	delta.x = (x - (master->cols - 1) / 2) * master->camera.zoom;
	dest->z = master->matrix[y][x] * z_zoom;
	depth = (float)y / (float)(master->rows - 1);
	brightness = (depth * 0.8) + 0.2;
	master->camera.offset_x = WIDTH / 2 + master->camera.x_add;
	master->camera.offset_y = (HEIGHT + master->max.z - master->min.z) * 0.8;
	master->camera.offset_y += master->camera.y_add;
	dest->y = (int)round(-dest->z + master->camera.offset_y);
	dest->x = (int)round(delta.x + master->camera.offset_x);
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

	z_zoom = master->camera.zoom * 0.5;
	delta.y = (y - (master->rows - 1) / 2) * master->camera.zoom;
	dest->z = master->matrix[y][x] * z_zoom;
	depth = (float)x / (float)(master->cols - 1);
	brightness = (depth * 0.8) + 0.2;
	master->camera.offset_x = WIDTH / 2 + master->camera.x_add;
	master->camera.offset_y = (HEIGHT + master->max.z - master->min.z) * 0.8;
	master->camera.offset_y += master->camera.y_add;
	dest->x = (int)round(delta.y + master->camera.offset_x);
	dest->y = (int)round(-dest->z + master->camera.offset_y);
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
