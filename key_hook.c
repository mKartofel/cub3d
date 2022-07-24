/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:49:49 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/24 15:46:55 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed_hook(int keycode, t_vars *vars)
{
	
	if (keycode == 65307)
		close_program(vars, 0);

	//move forward if no wall in front of you
	else if(keycode == 119)
		vars->move_forward = 1;
	//move backwards if no wall behind you
	else if(keycode == 115)
		vars->move_backward = 1;
	//move right if no wall in the way
	else if(keycode == 100)
		vars->move_right = 1;
	//move left if no wall in the way
	else if(keycode == 97)
		vars->move_left = 1;
	//rotate to the right
	if(keycode == 65363)
		vars->rotate_right = 1;
	//rotate to the left
	if(keycode == 65361)
		vars->rotate_left = 1;
	return (0);
}

int	key_released_hook(int keycode, t_vars *vars)
{
	if(keycode == 119)
		vars->move_forward = 0;
	else if(keycode == 115)
		vars->move_backward = 0;
	else if(keycode == 100)
		vars->move_right = 0;
	else if(keycode == 97)
		vars->move_left = 0;
	if(keycode == 65363)
		vars->rotate_right = 0;
	if(keycode == 65361)
		vars->rotate_left = 0;
	return (0);
}