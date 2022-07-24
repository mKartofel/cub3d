/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:07:05 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/24 17:16:12 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>

# define SCREENWIDTH 1080
# define SCREENHEIGHT 810
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define MAPWIDTH 24
# define MAPHEIGHT 24
# define NBTEXTURES 4

extern int worldmap[MAPWIDTH][MAPHEIGHT]; //enlever quand on a la vraie map !

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	movespeed;
	double	rotspeed;
	t_data	img1;
	t_data	img2;
	int		ceiling_color;
	int		floor_color;
	t_data	texture[NBTEXTURES];
	int		**worldmap;
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
	int		x;
}	t_vars;

int		raycasting(t_vars *vars);
void	draw_vertical_line(t_vars *vars, int begin_y, int end_y, int color);
void	swap_imgs(t_vars *vars);
void	custom_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int		get_pixel_color(t_data *data, int x, int y);
int		key_pressed_hook(int keycode, t_vars *vars);
int		key_released_hook(int keycode, t_vars *vars);
int		close_program(t_vars *vars, int ret);
void	load_textures(t_vars *vars);
void	init_vars_struct(t_vars *vars);
void	init_mlx_and_img_buffers(t_vars *vars);
void	set_init_direction(t_vars *vars, char dir);
void	player_movement(t_vars *vars);

#endif