/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:07:05 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/26 13:24:32 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx/mlx.h"
# include "libft/libft.h"
# include "./parsing/include/parsing.h"
# include <math.h>
# include <stdio.h>

# define SCREENWIDTH 1080
# define SCREENHEIGHT 810
# define NBTEXTURES 4

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
}	t_data;

typedef struct s_ray {
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	side_distx;
	double	side_disty;
	double	delta_distx;
	double	delta_disty;
	int		stepx;
	int		stepy;
	int		hit;
	char	side;
	double	perpwalldist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wallx;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;
	int		color;
}	t_ray;

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
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
	int		x;
	t_pars	*pars;
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
void	rotate_left(t_vars *vars);
void	rotate_right(t_vars *vars);
void	find_texture_to_draw(t_vars *vars, t_ray *ray);
void	draw_texture(t_vars *vars, t_ray *ray);
int		convert_rgb_to_trgb(int t, int r, int g, int b);

#endif