/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cu3d.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:07:05 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/22 18:58:05 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>

#define screenWidth 1080 //640
#define screenHeight 810 //480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define nbTextures 4

extern int worldMap[mapWidth][mapHeight]; //enlever quand on a la vraie map

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
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed;
	double rotSpeed;
	t_data img1;
	t_data img2;
	int ceiling_color;
	int floor_color;
	t_data texture[nbTextures];
	int **worldMap;
	int move_forward;
	int move_backward;
	int move_left;
	int move_right;
	int rotate_left;
	int rotate_right;
}	t_vars;


int		raycasting(t_vars *vars);
void	draw_line(t_vars *vars, int beginX, int beginY, int endX, int endY, int color);
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