/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:42:30 by buehara           #+#    #+#             */
/*   Updated: 2025/12/11 14:16:09 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include "src/Libft/includes/libft.h"
# include "src/Libft/includes/get_next_line.h"
# include "src/Libft/includes/ft_printf.h"

# define ANGLE 	0.523599f
# define HEX 	16

typedef struct	s_data
{
//	void	*mlx;
//	void	*window;
	void	*img;
	void	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_var
{
	void	*mlx;
	void	*window;
}				t_var;

typedef struct	s_master
{
	t_var	mlx;
	t_data	img;
	int		**matrix;
	int		cols;
	int		rows;
	int		color;
	int		**mcolor;
}				t_master;

typedef struct	s_axis
{
	int	x;
	int y;
	int z;
	int	color;
}				t_axis;

typedef struct	s_color
{
	short int	red;
	short int	green;
	short int	blue;
}				t_color;

// -------- Prototypes ---------
int		ishigher(int org, int dest);

void	pixel_put(t_data *data, int x, int y, int color);

void	bresenham(t_data *view, t_axis *org, t_axis dest, int color);

void	projection(int **matrix, int x, int y, t_axis *dest);

#endif
