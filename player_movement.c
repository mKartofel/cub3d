/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:35:39 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/24 16:43:36 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_forward_backward(t_vars *vars)
{
	//move forward if no wall in front of you
	if(vars->move_forward)
	{
		if(worldmap[(int)(vars->posx + vars->dirx * vars->movespeed)][(int)(vars->posy)] == 0) 
			vars->posx += vars->dirx * vars->movespeed;
		if(worldmap[(int)(vars->posx)][(int)(vars->posy + vars->diry * vars->movespeed)] == 0) 
			vars->posy += vars->diry * vars->movespeed;
	}
	//move backwards if no wall behind you
	if(vars->move_backward)
	{
		if(worldmap[(int)(vars->posx - vars->dirx * vars->movespeed)][(int)(vars->posy)] == 0)
			vars->posx -= vars->dirx * vars->movespeed;
		if(worldmap[(int)(vars->posx)][(int)(vars->posy - vars->diry * vars->movespeed)] == 0) 
			vars->posy -= vars->diry * vars->movespeed;
	}
}

void move_left_right(t_vars *vars)
{
	double dirx;
	double diry;
	double olddirx;
	double angle;
	
	//move right if no wall in the way
	if(vars->move_right)
	{
		dirx = vars->dirx;
		olddirx = dirx;
		diry = vars->diry;
		angle = 90 * M_PI / 180;
		dirx = dirx * cos(-angle) - diry * sin(-angle);
		diry = olddirx * sin(-angle) + diry * cos(-angle);
		if(worldmap[(int)(vars->posx + dirx * vars->movespeed)][(int)(vars->posy)] == 0)
			vars->posx += dirx * vars->movespeed;
		if(worldmap[(int)(vars->posx)][(int)(vars->posy + diry * vars->movespeed)] == 0)
			vars->posy += diry * vars->movespeed;
	}
	//move left if no wall in the way
	if(vars->move_left)
	{
		dirx = vars->dirx;
		olddirx = dirx;
		diry = vars->diry;
		angle = 90 * M_PI / 180;
		dirx = dirx * cos(angle) - diry * sin(angle);
		diry = olddirx * sin(angle) + diry * cos(angle);
		if(worldmap[(int)(vars->posx + dirx * vars->movespeed)][(int)(vars->posy)] == 0)
			vars->posx += dirx * vars->movespeed;
		if(worldmap[(int)(vars->posx)][(int)(vars->posy + diry * vars->movespeed)] == 0)
			vars->posy += diry * vars->movespeed;
	}
}

void rotate_left_right(t_vars *vars)
{
	double olddirx;
	double oldplanex;
	
	//rotate to the right
	if(vars->rotate_right)
	{
		//both camera direction and camera plane must be rotated
		olddirx = vars->dirx;
		vars->dirx = vars->dirx * cos(-vars->rotspeed) - vars->diry * sin(-vars->rotspeed);
		vars->diry = olddirx * sin(-vars->rotspeed) + vars->diry * cos(-vars->rotspeed);
		oldplanex = vars->planex;
		vars->planex = vars->planex * cos(-vars->rotspeed) - vars->planey * sin(-vars->rotspeed);
		vars->planey = oldplanex * sin(-vars->rotspeed) + vars->planey * cos(-vars->rotspeed);
	}
	//rotate to the left
	if(vars->rotate_left)
	{
		//both camera direction and camera plane must be rotated
		olddirx = vars->dirx;
		vars->dirx = vars->dirx * cos(vars->rotspeed) - vars->diry * sin(vars->rotspeed);
		vars->diry = olddirx * sin(vars->rotspeed) + vars->diry * cos(vars->rotspeed);
		oldplanex = vars->planex;
		vars->planex = vars->planex * cos(vars->rotspeed) - vars->planey * sin(vars->rotspeed);
		vars->planey = oldplanex * sin(vars->rotspeed) + vars->planey * cos(vars->rotspeed);
	}
}


void player_movement(t_vars *vars)
{
	move_forward_backward(vars);
	move_left_right(vars);
	rotate_left_right(vars);
}
