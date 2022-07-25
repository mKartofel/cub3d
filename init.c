/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:08:20 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/24 16:43:22 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialize members of the vars struct
 * 
 * @param vars 
 */
void	init_vars_struct(t_vars *vars)
{
	int	i;

	vars->mlx = NULL;
	vars->win = NULL;
	vars->img1.img = NULL;
	vars->img2.img = NULL;
	i = 0;
	while (i < NBTEXTURES)
	{
		vars->texture[i].img = NULL;
		i++;
	}
	vars->posx = 2;
	vars->posy = 4;
	vars->movespeed = 0.05;
	vars->rotspeed = 0.03;
	vars->move_forward = 0;
	vars->move_backward = 0;
	vars->move_left = 0;
	vars->move_right = 0;
	vars->rotate_left = 0;
	vars->rotate_right = 0;
}

/**
 * @brief Initialize mlx related variables, including images
 * 
 * @param vars 
 */
void	init_mlx_and_img_buffers(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		close_program(vars, 1);
	vars->win = mlx_new_window(vars->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	if (vars->win == NULL)
		close_program(vars, 1);
	vars->img1.img = mlx_new_image(vars->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (vars->img1.img == NULL)
		close_program(vars, 1);
	vars->img1.addr = mlx_get_data_addr(vars->img1.img,
			&vars->img1.bits_per_pixel, &vars->img1.line_length,
			&vars->img1.endian);
	if (vars->img1.addr == NULL)
		close_program(vars, 1);
	vars->img2.img = mlx_new_image(vars->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (vars->img2.img == NULL)
		close_program(vars, 1);
	vars->img2.addr = mlx_get_data_addr(vars->img2.img,
			&vars->img2.bits_per_pixel, &vars->img2.line_length,
			&vars->img2.endian);
	if (vars->img2.addr == NULL)
		close_program(vars, 1);
}

void	set_init_direction2(t_vars *vars, char dir)
{
	if (dir == 'E')
	{
		vars->dirx = 0;
		vars->diry = 1;
		vars->planex = 0.66;
		vars->planey = 0;
	}
	else if (dir == 'W')
	{
		vars->dirx = 0;
		vars->diry = -1;
		vars->planex = -0.66;
		vars->planey = 0;
	}
}

/**
 * @brief Set the initial direction/orientation of the player according to the
 * dir character argument.
 * @param vars 
 * @param dir N,S,E or W
 */
void	set_init_direction(t_vars *vars, char dir)
{
	if (dir == 'N')
	{
		vars->dirx = -1;
		vars->diry = 0;
		vars->planex = 0;
		vars->planey = 0.66;
	}
	else if (dir == 'S')
	{
		vars->dirx = 1;
		vars->diry = 0;
		vars->planex = 0;
		vars->planey = -0.66;
	}
	else
		set_init_direction2(vars, dir);
}
