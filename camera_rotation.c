/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:40:15 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/24 17:42:49 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_vars *vars)
{
	double	olddirx;
	double	oldplanex;

	if (vars->rotate_left)
	{
		olddirx = vars->dirx;
		vars->dirx = vars->dirx * cos(vars->rotspeed) - vars->diry
			* sin(vars->rotspeed);
		vars->diry = olddirx * sin(vars->rotspeed) + vars->diry
			* cos(vars->rotspeed);
		oldplanex = vars->planex;
		vars->planex = vars->planex * cos(vars->rotspeed) - vars->planey
			* sin(vars->rotspeed);
		vars->planey = oldplanex * sin(vars->rotspeed) + vars->planey
			* cos(vars->rotspeed);
	}
}

void	rotate_right(t_vars *vars)
{
	double	olddirx;
	double	oldplanex;

	if (vars->rotate_right)
	{
		olddirx = vars->dirx;
		vars->dirx = vars->dirx * cos(-vars->rotspeed) - vars->diry
			* sin(-vars->rotspeed);
		vars->diry = olddirx * sin(-vars->rotspeed) + vars->diry
			* cos(-vars->rotspeed);
		oldplanex = vars->planex;
		vars->planex = vars->planex * cos(-vars->rotspeed) - vars->planey
			* sin(-vars->rotspeed);
		vars->planey = oldplanex * sin(-vars->rotspeed) + vars->planey
			* cos(-vars->rotspeed);
	}
}
