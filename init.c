/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:08:20 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/22 18:48:02 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cu3d.h"

void	init_vars_struct(t_vars *vars)
{
	int i;
	
	vars->mlx = NULL;
	vars->win = NULL;
	vars->img1.img = NULL;
	vars->img2.img = NULL;
	i = 0;
	while (i < nbTextures)
	{
		vars->texture[i].img = NULL;
		i++;
	}
	//x and y start position
	vars->posX = 2;
	vars->posY = 4;
	vars->moveSpeed = 0.1; //squares/second
	vars->rotSpeed = 0.06; //radians/second
	
	vars->move_forward = 0;
	vars->move_backward = 0;
	vars->move_left = 0;
	vars->move_right = 0;
	vars->rotate_left = 0;
	vars->rotate_right = 0;
}

void init_mlx_and_img_buffers(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		close_program(vars, 1);
	vars->win = mlx_new_window(vars->mlx, screenWidth, screenHeight, "cub3d");
	if (vars->win == NULL)
		close_program(vars, 1);
	vars->img1.img = mlx_new_image(vars->mlx, screenWidth, screenHeight);
	if (vars->img1.img == NULL)
		close_program(vars, 1);
	vars->img1.addr = mlx_get_data_addr(vars->img1.img, &vars->img1.bits_per_pixel, &vars->img1.line_length, &vars->img1.endian);
	if (vars->img1.addr == NULL)
		close_program(vars, 1);
	vars->img2.img = mlx_new_image(vars->mlx, screenWidth, screenHeight);
	if (vars->img2.img == NULL)
		close_program(vars, 1);
	vars->img2.addr = mlx_get_data_addr(vars->img2.img, &vars->img2.bits_per_pixel, &vars->img2.line_length, &vars->img2.endian);
	if (vars->img2.addr == NULL)
		close_program(vars, 1);
}

/**
 * @brief Set the initial direction/orientation of the player according to the
 * dir character argument.
 * @param vars 
 * @param dir N,S,E or W
 */
void set_init_direction(t_vars *vars, char dir)
{
	if (dir == 'N')
	{
		//initial direction vector
		vars->dirX = -1;
		vars->dirY = 0; 
		//the 2d raycaster version of camera plane
		vars->planeX = 0;
		vars->planeY = 0.66; 
	}
	else if (dir == 'S')
	{
		vars->dirX = 1;
		vars->dirY = 0; 
		vars->planeX = 0;
		vars->planeY = -0.66; 
	}
	else if (dir == 'E')
	{
		vars->dirX = 0;
		vars->dirY = 1; 
		vars->planeX = 0.66;
		vars->planeY = 0; 
	}
	else if (dir == 'W')
	{
		vars->dirX = 0;
		vars->dirY = -1; 
		vars->planeX = -0.66;
		vars->planeY = 0; 
	}
}