/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:55:55 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/30 11:15:04 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cu3d.h"

void	custom_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->img1.addr + (y * vars->img1.line_length + x * (vars->img1.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_pixel_color(t_data *data, int x, int y)
{
	char	*color;

	color = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return *(unsigned int*)color;
}

void draw_line(t_vars *vars, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX;
	double deltaY;
	double pixelX;
	double pixelY;
	int pixels;
	
	deltaX = endX - beginX; 
	deltaY = endY - beginY; 
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		custom_mlx_pixel_put(vars, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}