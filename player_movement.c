/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:35:39 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/26 13:04:01 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward_backward(t_vars *vars)
{
	if (vars->move_forward)
	{
		if (vars->pars->tab[(int)(vars->posx + vars->dirx * vars->movespeed)]
				[(int)(vars->posy)] == 0)
			vars->posx += vars->dirx * vars->movespeed;
		if (vars->pars->tab[(int)(vars->posx)][(int)(vars->posy + vars->diry
				* vars->movespeed)] == 0)
			vars->posy += vars->diry * vars->movespeed;
	}
	if (vars->move_backward)
	{
		if (vars->pars->tab[(int)(vars->posx - vars->dirx * vars->movespeed)]
				[(int)(vars->posy)] == 0)
			vars->posx -= vars->dirx * vars->movespeed;
		if (vars->pars->tab[(int)(vars->posx)][(int)(vars->posy - vars->diry
				* vars->movespeed)] == 0)
			vars->posy -= vars->diry * vars->movespeed;
	}
}

void	move_left(t_vars *vars)
{
	double	dirx;
	double	diry;
	double	olddirx;
	double	angle;

	if (vars->move_left)
	{
		dirx = vars->dirx;
		olddirx = dirx;
		diry = vars->diry;
		angle = 90 * M_PI / 180;
		dirx = dirx * cos(angle) - diry * sin(angle);
		diry = olddirx * sin(angle) + diry * cos(angle);
		if (vars->pars->tab[(int)(vars->posx + dirx * vars->movespeed)]
			[(int)(vars->posy)] == 0)
			vars->posx += dirx * vars->movespeed;
		if (vars->pars->tab[(int)(vars->posx)][(int)(vars->posy + diry
			* vars->movespeed)] == 0)
			vars->posy += diry * vars->movespeed;
	}
}

void	move_right(t_vars *vars)
{
	double	dirx;
	double	diry;
	double	olddirx;
	double	angle;

	if (vars->move_right)
	{
		dirx = vars->dirx;
		olddirx = dirx;
		diry = vars->diry;
		angle = 90 * M_PI / 180;
		dirx = dirx * cos(-angle) - diry * sin(-angle);
		diry = olddirx * sin(-angle) + diry * cos(-angle);
		if (vars->pars->tab[(int)(vars->posx + dirx * vars->movespeed)]
			[(int)(vars->posy)] == 0)
			vars->posx += dirx * vars->movespeed;
		if (vars->pars->tab[(int)(vars->posx)][(int)(vars->posy + diry
			* vars->movespeed)] == 0)
			vars->posy += diry * vars->movespeed;
	}
}

void	player_movement(t_vars *vars)
{
	move_forward_backward(vars);
	move_left(vars);
	move_right(vars);
	rotate_left(vars);
	rotate_right(vars);
}
