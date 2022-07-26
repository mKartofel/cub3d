/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:49:49 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/26 21:51:29 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_program(vars, 0, NULL);
	else if (keycode == 119)
		vars->move_forward = 1;
	else if (keycode == 115)
		vars->move_backward = 1;
	else if (keycode == 100)
		vars->move_right = 1;
	else if (keycode == 97)
		vars->move_left = 1;
	if (keycode == 65363)
		vars->rotate_right = 1;
	if (keycode == 65361)
		vars->rotate_left = 1;
	return (0);
}

int	key_released_hook(int keycode, t_vars *vars)
{
	if (keycode == 119)
		vars->move_forward = 0;
	else if (keycode == 115)
		vars->move_backward = 0;
	else if (keycode == 100)
		vars->move_right = 0;
	else if (keycode == 97)
		vars->move_left = 0;
	if (keycode == 65363)
		vars->rotate_right = 0;
	if (keycode == 65361)
		vars->rotate_left = 0;
	return (0);
}
