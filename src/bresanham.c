/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresanham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:29:23 by buehara           #+#    #+#             */
/*   Updated: 2025/12/18 19:49:46 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	projection(t_master *master, int x, int y, t_axis *dest)
{
	if (master->projection == ISO)
		project_iso(master, x, y, dest);
}

void	project_iso(t_master *master, int x, int y, t_axis *dest)
{
	double	dx;
	double	dy;
	double	z;
	double	z_zoom;
	double	temp_dx;

	if (master->color)
		dest->color = master->mcolor[y][x];
	else
		dest->color = DEFCOLOR;
	z_zoom = master->zoom * 0.5;
	z = master->matrix[y][x] * z_zoom;
	dx = x - master->cols / 2;
	dy = y - master->rows / 2;
	dx *= master->zoom;
	dy *= master->zoom;
	temp_dx = dx;
	dx = (temp_dx - dy) * cos(ANGLE);
	dy = (temp_dx + dy) * sin(ANGLE) - z;
	dx += master->offset_x;
	dy += master->offset_y;
	dest->x = (int)round(dx);
	dest->y = (int)round(dy);
}

static void	swap_vars(t_axis *cal, t_axis *org, t_axis *dest, t_axis *diff)
{
	ft_void_swap(&cal->x, &cal->y, sizeof(int));
	ft_void_swap(&org->x, &org->y, sizeof(int));
	ft_void_swap(&dest->x, &dest->y, sizeof(int));
	ft_void_swap(&diff->x, &diff->y, sizeof(int));
}

static void	bres_util(t_axis *org, t_axis cal, double *bress, t_axis diff)
{
	org->x += diff.x;
	if (*bress >= 0)
	{
		org->y += diff.y;
		*bress += 2 * cal.y - 2 * cal.x;
	}
	else
		*bress += 2 * cal.y;
}

void	bresanham(t_data *view, t_axis org, t_axis dest)
{
	double	bress;
	t_axis	cal;
	t_axis	diff;
	int		color;

	cal.x = abs(dest.x - org.x);
	cal.y = abs(dest.y - org.y);
	diff.x = ishigher(org.x, dest.x);
	diff.y = ishigher(org.y, dest.y);
	view->steep = OFF;
	if (cal.y > cal.x)
	{
		view->steep = ON;
		swap_vars(&cal, &org, &dest, &diff);
	}
	bress = 2 * cal.y - cal.x;
	while (org.x != dest.x || org.y != dest.y)
	{
		if (org.color != dest.color)
			color = color_att(org, dest, cal);
		else
			color = dest.color;
		pixel_put(view, org.x, org.y, color);
		bres_util(&org, cal, &bress, diff);
	}
}
