/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:23:28 by buehara           #+#    #+#             */
/*   Updated: 2025/12/20 14:17:55 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static t_color	color_rgb(t_axis point)
{
	t_color	color;

	color.red = (point.color & MASKRED) >> 16;
	color.green = (point.color & MASKGREEN) >> 8;
	color.blue = point.color & MASKBLUE;
	return (color);
}

int	color_att(t_axis org, t_axis dest, t_axis cal)
{
	t_color	og_col;
	t_color	dst_col;
	t_color	ncolor;
	float	ratio;
	int		color;

	og_col = color_rgb(org);
	dst_col = color_rgb(dest);
	if (org.x > dest.x)
		ft_void_swap(&org.x, &dest.x, sizeof(int));
	ratio = (float)(org.x - (dest.x - cal.x)) / cal.x;
	ncolor.red = (1 - ratio) * og_col.red + dst_col.red * ratio;
	ncolor.green = (1 - ratio) * og_col.green + dst_col.green * ratio;
	ncolor.blue = (1 - ratio) * og_col.blue + dst_col.blue * ratio;
	color = (ncolor.red << 16) | (ncolor.green << 8) | ncolor.blue;
	return (color);
}

int	depth_color(int color, float ratio)
{
	t_color		rgb;
	long double	color_depth;

	rgb.red = ((color >> 16) & 0xFF) * ratio;
	rgb.green = ((color >> 8) & 0xFF) * ratio;
	rgb.blue = (color & 0xFF) * ratio;
	color_depth = (rgb.red << 16) | (rgb.green << 8) | rgb.blue;
	return (color_depth);
}
