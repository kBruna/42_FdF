/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:42:30 by buehara           #+#    #+#             */
/*   Updated: 2025/12/13 11:38:11 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
//# include <OpenGL/gl.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include "src/Libft/includes/libft.h"
# include "src/Libft/includes/get_next_line.h"
# include "src/Libft/includes/ft_printf.h"

# define ANGLE 		0.523599f
# define HEX 		16
# define WIDTH		1920
# define HEIGHT 	1030
# define ZOOM_BASE	50

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
	double	zoom;
	int		**matrix;
	int		**mcolor;
	int		cols;
	int		rows;
	int		color;
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

// -------- Matrix.c -------------
int		**matrix_double(t_master *master);
int		**matrix_make(t_master *master);
void	matrix_free(int **matrix, int rows);

// -------- Matrix_utils.c -------
int		matrix_fill(int fd, t_master *master);
int		matrix_init(t_master *master, int fd);
void	matrix_error(int **color, t_master *master);

// -------- FDF_MLX_utils.c ---------
int		open_map(int argc, char **argv);
int		ft_mlx_init(t_master *master);
int		key_map(int keycode, t_master *master);
int		close_program(t_master *master);
void	pixel_put(t_data *data, int x, int y, int color);

// -------- parsing.c --------------
int		ft_atoi_hex(char *nbr, int base);
int		count_num(t_master *master, int fd);
char	*get_buffer(int fd);
void	buffer_check(char *buffer, int *cols, int *color);
void	values_checker(char *buf, t_master *master, int *index, t_axis *id);

// -------- main.c -----------------
void	zoom_init(t_master *master);

int		ishigher(int org, int dest);

void	pixel_put(t_data *data, int x, int y, int color);

void	bresenham(t_data *view, t_axis *org, t_axis dest, int color);

void	projection(t_master *master, int x, int y, t_axis *dest);

#endif
