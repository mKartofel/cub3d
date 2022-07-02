/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:12:23 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/30 11:40:27 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cu3d.h"

int raycasting(t_vars *vars)
{
	int x;

	x = 0;
	while (x < screenWidth)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double raydirX = vars->dirX + vars->planeX * cameraX;
		double raydirY = vars->dirY + vars->planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)(vars->posX);
		int mapY = (int)(vars->posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (rayvars.dirY * rayvars.dirY) / (rayvars.dirX * rayvars.dirX))
		//deltaDistY = sqrt(1 + (rayvars.dirX * rayvars.dirX) / (rayvars.dirY * rayvars.dirY))
		//which can be simplified to abs(|rayDir| / rayvars.dirX) and abs(|rayDir| / rayvars.dirY)
		//where |rayDir| is the length of the vector (rayvars.dirX, rayvars.dirY). Its length,
		//unlike (vars->dirX, vars->dirY) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.
		double deltaDistX = (raydirX == 0) ? 1e30 : fabs(1 / raydirX);
		double deltaDistY = (raydirY == 0) ? 1e30 : fabs(1 / raydirY);

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		char side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(raydirX < 0)
		{
			stepX = -1;
			sideDistX = (vars->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - vars->posX) * deltaDistX;
		}
		if(raydirY < 0)
		{
			stepY = -1;
			sideDistY = (vars->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - vars->posY) * deltaDistY;
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
			if(worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / raydirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(side == 'N' || side == 'S') perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

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
		if (side == 'N' || side == 'S') wallX = vars->posY + perpWallDist * raydirY;
		else           wallX = vars->posX + perpWallDist * raydirX;
		wallX -= floor((wallX)); //substrat integer value from it (only keep decimal value)

		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if((side == 'N' || side == 'S') && raydirX > 0)
			texX = texWidth - texX - 1;
		if((side == 'E' || side == 'W') && raydirY < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
				
			int color = get_pixel_color(&vars->texture[texNum], texX, texY);
			custom_mlx_pixel_put(vars, x, y, color);
		}
		draw_line(vars, x, 0, x, drawStart, vars->ceiling_color); //draw ceiling line
		draw_line(vars, x, drawEnd, x, screenHeight, vars->floor_color); //draw floor line
		x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img1.img, 0, 0);
	swap_imgs(vars);
	return (0);
}