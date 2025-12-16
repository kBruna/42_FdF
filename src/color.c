/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:23:28 by buehara           #+#    #+#             */
/*   Updated: 2025/12/15 21:43:23 by buehara          ###   ########.fr       */
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
	t_color og_col;
	t_color	dst_col;
	t_color	ncolor;
	float	ratio;
	int		color;

	og_col = color_rgb(org);
	dst_col = color_rgb(dest);
	ratio = (float)org.x / cal.x;
	ncolor.red = og_col.red + (int)((dst_col.red - og_col.red)) * ratio;
	ncolor.green = og_col.green + (int)((dst_col.green - og_col.green)) * ratio;
	ncolor.blue = og_col.blue + (int)((dst_col.blue - og_col.blue)) * ratio;
	color = (ncolor.red << 16) | (ncolor.blue << 8) | ncolor.blue;
	return (color);
}
//TODO : Corrigir a gradacao de cor mds
