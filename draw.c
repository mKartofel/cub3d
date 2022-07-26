/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:55:55 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/26 14:26:23 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	custom_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	// printf("x=%d\n", x);
	// printf("y=%d\n", y);
	dst = vars->img1.addr + (y * vars->img1.line_length + x
			* (vars->img1.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_data *data, int x, int y)
{
	char	*color;

	color = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	return (*(unsigned int *)color);
}

void	draw_vertical_line(t_vars *vars, int begin_y, int end_y, int color)
{
	double	pixel_y;
	int		pixels_to_draw;

	pixels_to_draw = end_y - begin_y;
	pixel_y = begin_y;
	while (pixels_to_draw)
	{
		custom_mlx_pixel_put(vars, vars->x, pixel_y, color);
		pixel_y++;
		pixels_to_draw--;
	}
}
