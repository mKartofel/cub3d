/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:35:39 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/22 18:54:22 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cu3d.h"

void player_movement(t_vars *vars)
{
	move_forward_backward(vars);
	move_left_right(vars);
	rotate_left_right(vars);
}

void move_forward_backward(t_vars *vars)
{
	//move forward if no wall in front of you
	if(vars->move_forward)
	{
		if(worldMap[(int)(vars->posX + vars->dirX * vars->moveSpeed)][(int)(vars->posY)] == 0) 
			vars->posX += vars->dirX * vars->moveSpeed;
		if(worldMap[(int)(vars->posX)][(int)(vars->posY + vars->dirY * vars->moveSpeed)] == 0) 
			vars->posY += vars->dirY * vars->moveSpeed;
	}
	//move backwards if no wall behind you
	if(vars->move_backward)
	{
		if(worldMap[(int)(vars->posX - vars->dirX * vars->moveSpeed)][(int)(vars->posY)] == 0)
			vars->posX -= vars->dirX * vars->moveSpeed;
		if(worldMap[(int)(vars->posX)][(int)(vars->posY - vars->dirY * vars->moveSpeed)] == 0) 
			vars->posY -= vars->dirY * vars->moveSpeed;
	}
}

void move_left_right(t_vars *vars)
{
	double dirX;
	double dirY;
	double olddirX;
	double angle;
	
	//move right if no wall in the way
	if(vars->move_right)
	{
		dirX = vars->dirX;
		olddirX = dirX;
		dirY = vars->dirY;
		angle = 90 * M_PI / 180;
		dirX = dirX * cos(-angle) - dirY * sin(-angle);
		dirY = olddirX * sin(-angle) + dirY * cos(-angle);
		if(worldMap[(int)(vars->posX + dirX * vars->moveSpeed)][(int)(vars->posY)] == 0)
			vars->posX += dirX * vars->moveSpeed;
		if(worldMap[(int)(vars->posX)][(int)(vars->posY + dirY * vars->moveSpeed)] == 0)
			vars->posY += dirY * vars->moveSpeed;
	}
	//move left if no wall in the way
	if(vars->move_left)
	{
		dirX = vars->dirX;
		olddirX = dirX;
		dirY = vars->dirY;
		angle = 90 * M_PI / 180;
		dirX = dirX * cos(angle) - dirY * sin(angle);
		dirY = olddirX * sin(angle) + dirY * cos(angle);
		if(worldMap[(int)(vars->posX + dirX * vars->moveSpeed)][(int)(vars->posY)] == 0)
			vars->posX += dirX * vars->moveSpeed;
		if(worldMap[(int)(vars->posX)][(int)(vars->posY + dirY * vars->moveSpeed)] == 0)
			vars->posY += dirY * vars->moveSpeed;
	}
}

void rotate_left_right(t_vars *vars)
{
	double olddirX;
	double oldplaneX;
	
	//rotate to the right
	if(vars->rotate_right)
	{
		//both camera direction and camera plane must be rotated
		olddirX = vars->dirX;
		vars->dirX = vars->dirX * cos(-vars->rotSpeed) - vars->dirY * sin(-vars->rotSpeed);
		vars->dirY = olddirX * sin(-vars->rotSpeed) + vars->dirY * cos(-vars->rotSpeed);
		oldplaneX = vars->planeX;
		vars->planeX = vars->planeX * cos(-vars->rotSpeed) - vars->planeY * sin(-vars->rotSpeed);
		vars->planeY = oldplaneX * sin(-vars->rotSpeed) + vars->planeY * cos(-vars->rotSpeed);
	}
	//rotate to the left
	if(vars->rotate_left)
	{
		//both camera direction and camera plane must be rotated
		olddirX = vars->dirX;
		vars->dirX = vars->dirX * cos(vars->rotSpeed) - vars->dirY * sin(vars->rotSpeed);
		vars->dirY = olddirX * sin(vars->rotSpeed) + vars->dirY * cos(vars->rotSpeed);
		oldplaneX = vars->planeX;
		vars->planeX = vars->planeX * cos(vars->rotSpeed) - vars->planeY * sin(vars->rotSpeed);
		vars->planeY = oldplaneX * sin(vars->rotSpeed) + vars->planeY * cos(vars->rotSpeed);
	}
}
