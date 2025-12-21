/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresanham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:29:23 by buehara           #+#    #+#             */
/*   Updated: 2025/12/21 20:28:44 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
		color = color_att(org, dest, cal);
		pixel_put(view, org.x, org.y, color);
		bres_util(&org, cal, &bress, diff);
	}
}
