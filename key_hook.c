/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:49:49 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/30 10:54:34 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cu3d.h"

/*Map key_codes to functions*/
int	key_hook(int keycode, t_vars *vars)
{
	double dirX;
	double dirY;
	double olddirX;
	double oldplaneX;
	double angle;
	
	if (keycode == 65307)
		close_program(vars, 0);
	//move forward if no wall in front of you
	if(keycode == 119)
	{
		if(worldMap[(int)(vars->posX + vars->dirX * vars->moveSpeed)][(int)(vars->posY)] == 0) 
			vars->posX += vars->dirX * vars->moveSpeed;
		if(worldMap[(int)(vars->posX)][(int)(vars->posY + vars->dirY * vars->moveSpeed)] == 0) 
			vars->posY += vars->dirY * vars->moveSpeed;
	}
	//move backwards if no wall behind you
	if(keycode == 115)
	{
		if(worldMap[(int)(vars->posX - vars->dirX * vars->moveSpeed)][(int)(vars->posY)] == 0)
			vars->posX -= vars->dirX * vars->moveSpeed;
		if(worldMap[(int)(vars->posX)][(int)(vars->posY - vars->dirY * vars->moveSpeed)] == 0) 
			vars->posY -= vars->dirY * vars->moveSpeed;
	}
	//move right if no wall in the way
	if(keycode == 100)
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
	if(keycode == 97)
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
	//rotate to the right
	if(keycode == 65363)
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
	if(keycode == 65361)
	{
		//both camera direction and camera plane must be rotated
		olddirX = vars->dirX;
		vars->dirX = vars->dirX * cos(vars->rotSpeed) - vars->dirY * sin(vars->rotSpeed);
		vars->dirY = olddirX * sin(vars->rotSpeed) + vars->dirY * cos(vars->rotSpeed);
		oldplaneX = vars->planeX;
		vars->planeX = vars->planeX * cos(vars->rotSpeed) - vars->planeY * sin(vars->rotSpeed);
		vars->planeY = oldplaneX * sin(vars->rotSpeed) + vars->planeY * cos(vars->rotSpeed);
	}
	return (0);
}