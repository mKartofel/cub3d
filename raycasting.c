/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:12:23 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/24 16:57:09 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int raycasting(t_vars *vars)
{
	int x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)SCREENWIDTH - 1; //x-coordinate in camera space
		double raydirx = vars->dirx + vars->planex * cameraX;
		double raydiry = vars->diry + vars->planey * cameraX;
		//which box of the map we're in
		int mapX = (int)(vars->posx);
		int mapY = (int)(vars->posy);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (rayvars.diry * rayvars.diry) / (rayvars.dirx * rayvars.dirx))
		//deltaDistY = sqrt(1 + (rayvars.dirx * rayvars.dirx) / (rayvars.diry * rayvars.diry))
		//which can be simplified to abs(|rayDir| / rayvars.dirx) and abs(|rayDir| / rayvars.diry)
		//where |rayDir| is the length of the vector (rayvars.dirx, rayvars.diry). Its length,
		//unlike (vars->dirx, vars->diry) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.
		double deltaDistX = (raydirx == 0) ? 1e30 : fabs(1 / raydirx);
		double deltaDistY = (raydiry == 0) ? 1e30 : fabs(1 / raydiry);

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		char side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(raydirx < 0)
		{
			stepX = -1;
			sideDistX = (vars->posx - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - vars->posx) * deltaDistX;
		}
		if(raydiry < 0)
		{
			stepY = -1;
			sideDistY = (vars->posy - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - vars->posy) * deltaDistY;
		}
		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				if (stepX == 1)
					side = 'N';
				else if (stepX == -1)
					side = 'S';
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				if (stepY == -1)
					side = 'E';
				else if (stepY == 1)
					side = 'W';
			}
			//Check if ray has hit a wall
			if(worldmap[mapX][mapY] > 0)
				hit = 1;
		}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posx + (1 - stepX) / 2) / raydirx for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(side == 'N' || side == 'S') perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCREENHEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
		if(drawEnd >= SCREENHEIGHT) drawEnd = SCREENHEIGHT - 1;

		//select the correct texture to use
		int texNum;
		if (side == 'N')
			texNum = 0;
		else if (side == 'S')
			texNum = 1;
		else if (side == 'E')
			texNum = 2;
		else if (side == 'W')
			texNum = 3;	

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 'N' || side == 'S') wallX = vars->posy + perpWallDist * raydiry;
		else           wallX = vars->posx + perpWallDist * raydirx;
		wallX -= floor((wallX)); //substrat integer value from it (only keep decimal value)

		//x coordinate on the texture
		int texX = (int)(wallX * (double)TEXWIDTH);
		if((side == 'N' || side == 'S') && raydirx > 0)
			texX = TEXWIDTH - texX - 1;
		if((side == 'E' || side == 'W') && raydiry < 0)
			texX = TEXWIDTH - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TEXHEIGHT / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - SCREENHEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (TEXHEIGHT - 1) in case of overflow
			int texY = (int)texPos & (TEXHEIGHT - 1);
			texPos += step;
				
			int color = get_pixel_color(&vars->texture[texNum], texX, texY);
			custom_mlx_pixel_put(vars, x, y, color);
		}
		draw_vertical_line(vars, x, 0, drawStart, vars->ceiling_color); //draw ceiling line
		draw_vertical_line(vars, x, drawEnd, SCREENHEIGHT, vars->floor_color); //draw floor line
		x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img1.img, 0, 0);

	player_movement(vars);

	swap_imgs(vars);
	return (0);
}