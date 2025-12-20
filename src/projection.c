/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:19:56 by buehara           #+#    #+#             */
/*   Updated: 2025/12/20 19:10:55 by buehara          ###   ########.fr       */
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

	z_zoom = master->zoom * 0.25;
	dest->z = master->matrix[y][x] * z_zoom;
	delta.x = (x - (master->cols - 1) / 2) * master->zoom;
	delta.y = (y - (master->rows - 1) / 2) * master->zoom;
	temp_dx = delta.x;
	delta.x = (temp_dx - delta.y) * cos(ANGLE);
	delta.y = (temp_dx + delta.y) * sin(ANGLE) - dest->z;
	master->offset_x = WIDTH / 2;
	master->offset_y = (HEIGHT) * 0.5;
	dest->x = (int)round(delta.x + master->offset_x);
	dest->y = (int)round(delta.y + master->offset_y);
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

	z_zoom = master->zoom * 0.5;
	delta.x = (x - (master->cols - 1) / 2) * master->zoom;
	delta.y = (y - (master->rows - 1) / 2) * master->zoom;
	depth = (float)master->matrix[y][x] / (float)(master->max.z + master->min.z);
	brightness = (depth * 0.8) + 0.2;
	master->offset_x = WIDTH / 2;
	master->offset_y = HEIGHT / 2;
	dest->x = (int)round(delta.x + master->offset_x);
	dest->y = (int)round(delta.y + master->offset_y);
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

	z_zoom = master->zoom * 0.5;
	delta.x = (x - (master->cols - 1) / 2) * master->zoom;
	dest->z = master->matrix[y][x] * z_zoom;
	depth = (float)y / (float)(master->rows - 1);
	brightness = (depth * 0.8) + 0.2;
	master->offset_x = WIDTH / 2;
	master->offset_y = (HEIGHT + master->max.z - master->min.z) * 0.8;
	dest->y = (int)round(-dest->z + master->offset_y);
	dest->x = (int)round(delta.x + master->offset_x);
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

	z_zoom = master->zoom * 0.5;
	delta.y = (y - (master->rows - 1) / 2) * master->zoom;
	dest->z = master->matrix[y][x] * z_zoom;
	depth = (float)x / (float)(master->cols - 1);
	brightness = (depth * 0.8) + 0.2;
	master->offset_x = WIDTH / 2;
	master->offset_y = (HEIGHT + master->max.z - master->min.z) * 0.8;
	dest->x = (int)round(delta.y + master->offset_x);
	dest->y = (int)round(-dest->z + master->offset_y);
	if (master->color)
		dest->color = depth_color(master->mcolor[y][x], brightness);
	else
		dest->color = depth_color(DEFCOLOR, brightness);
}

void	projection(t_master *master, int x, int y, t_axis *dest)
{
	if (master->projection == ISO)
		project_iso(master, x, y, dest);
	else if (master->projection == TOP_VIEW)
		project_top(master, x, y, dest);
	else if (master->projection == X_VIEW)
		project_x(master, x, y, dest);
	else if (master->projection == Y_VIEW)
		project_y(master, x, y, dest); 
}
