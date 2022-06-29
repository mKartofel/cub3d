/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:13:37 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/29 15:57:19 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cu3d.h"

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

void	free_vars(t_vars *vars)
{
	// free(vars->map);
	// if (vars->player_img != NULL)
	// 	mlx_destroy_image(vars->mlx, vars->player_img);
	// if (vars->ground_img != NULL)
	// 	mlx_destroy_image(vars->mlx, vars->ground_img);
	// if (vars->wall_img != NULL)
	// 	mlx_destroy_image(vars->mlx, vars->wall_img);
	// if (vars->collectible_img != NULL)
	// 	mlx_destroy_image(vars->mlx, vars->collectible_img);
	// if (vars->exit_img != NULL)
	// 	mlx_destroy_image(vars->mlx, vars->exit_img);
	// if (vars->player_on_exit_img != NULL)
	// 	mlx_destroy_image(vars->mlx, vars->player_on_exit_img);
	if (vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx != NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
}

int	close_program(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	free_vars(vars);
	exit(1);
}



void	init_vars_struct(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
}

/*Map key_codes to functions*/
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_program(vars);
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
		double dirX = vars->dirX;
		double olddirX = dirX;
		double dirY = vars->dirY;
		double angle = 90 * M_PI / 180;
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
		double dirX = vars->dirX;
		double olddirX = dirX;
		double dirY = vars->dirY;
		double angle = 90 * M_PI / 180;
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
		double olddirX = vars->dirX;
		vars->dirX = vars->dirX * cos(-vars->rotSpeed) - vars->dirY * sin(-vars->rotSpeed);
		vars->dirY = olddirX * sin(-vars->rotSpeed) + vars->dirY * cos(-vars->rotSpeed);
		double oldplaneX = vars->planeX;
		vars->planeX = vars->planeX * cos(-vars->rotSpeed) - vars->planeY * sin(-vars->rotSpeed);
		vars->planeY = oldplaneX * sin(-vars->rotSpeed) + vars->planeY * cos(-vars->rotSpeed);
	}
	//rotate to the left
	if(keycode == 65361)
	{
		//both camera direction and camera plane must be rotated
		double olddirX = vars->dirX;
		vars->dirX = vars->dirX * cos(vars->rotSpeed) - vars->dirY * sin(vars->rotSpeed);
		vars->dirY = olddirX * sin(vars->rotSpeed) + vars->dirY * cos(vars->rotSpeed);
		double oldplaneX = vars->planeX;
		vars->planeX = vars->planeX * cos(vars->rotSpeed) - vars->planeY * sin(vars->rotSpeed);
		vars->planeY = oldplaneX * sin(vars->rotSpeed) + vars->planeY * cos(vars->rotSpeed);
	}
	return (0);
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
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
	double deltaX = endX - beginX; 
	double deltaY = endY - beginY; 
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		my_mlx_pixel_put(vars, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

void	swap_imgs(t_vars *vars)
{
	void *tmp;

	tmp = vars->img1.img;
	vars->img1.img = vars->img2.img;
	vars->img2.img = tmp;
	tmp = vars->img1.addr;
	vars->img1.addr = vars->img2.addr;
	vars->img2.addr = tmp;
	//and bits / length ?
}

int raycasting(t_vars *vars)
{

	// clock_t begin = clock();
	
	for(int x = 0; x < screenWidth; x++)
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
		int side; //was a NS or a EW wall hit?
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
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if(worldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / raydirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

		//texturing calculations
		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = vars->posY + perpWallDist * raydirY;
		else           wallX = vars->posX + perpWallDist * raydirX;
		wallX -= floor((wallX)); //substrat integer value from it (only keep decimal value)

		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && raydirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && raydirY < 0) texX = texWidth - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			// int color = vars->texture[texNum].img[texHeight * texY + texX];
			int color = get_pixel_color(&vars->texture[texNum], texX, texY);
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
				// buffer[y][x] = color;
				my_mlx_pixel_put(vars, x, y, color);
		}

		//draw the pixels of the stripe as a vertical line
		draw_line(vars, x, 0, x, drawStart, vars->ceiling_color); //draw ceiling line
		// draw_line(vars, x, drawStart, x, drawEnd, color);
		draw_line(vars, x, drawEnd, x, screenHeight, vars->floor_color); //draw floor line
	}

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img1.img, 0, 0);

	//timing for input and FPS counter
	// clock_t end = clock();
	// double frameTime = (end - begin) / 1000.0; //frameTime is the time this frame has taken, in seconds
	// printf("%f\n", 1.0 / frameTime); //FPS counter
	// redraw();
	// cls();

	//speed modifiers
	// vars->moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	// vars->rotSpeed = frameTime * 3.0; //the constant value is in radians/second

	swap_imgs(vars);
	
	return (0);
}

/*Load the images for the game assets from the .xpm files*/
void	load_images(t_vars *vars)
{
	int		img_width;
	int		img_height;

	//PROTECT ALL
	vars->texture[0].img = mlx_xpm_file_to_image(vars->mlx, "images/eagle.xpm", &img_width, &img_height);
	vars->texture[0].addr = mlx_get_data_addr(vars->texture[0].img, &vars->texture[0].bits_per_pixel, &vars->texture[0].line_length, &vars->texture[0].endian);

	vars->texture[1].img = mlx_xpm_file_to_image(vars->mlx, "images/redbrick.xpm", &img_width, &img_height);
	vars->texture[1].addr = mlx_get_data_addr(vars->texture[1].img, &vars->texture[1].bits_per_pixel, &vars->texture[1].line_length, &vars->texture[1].endian);

	vars->texture[2].img = mlx_xpm_file_to_image(vars->mlx, "images/purplestone.xpm", &img_width, &img_height);
	vars->texture[2].addr = mlx_get_data_addr(vars->texture[2].img, &vars->texture[2].bits_per_pixel, &vars->texture[2].line_length, &vars->texture[2].endian);

	vars->texture[3].img = mlx_xpm_file_to_image(vars->mlx, "images/greystone.xpm", &img_width, &img_height);
	vars->texture[3].addr = mlx_get_data_addr(vars->texture[3].img, &vars->texture[3].bits_per_pixel, &vars->texture[3].line_length, &vars->texture[3].endian);

	vars->texture[4].img = mlx_xpm_file_to_image(vars->mlx, "images/bluestone.xpm", &img_width, &img_height);
	vars->texture[4].addr = mlx_get_data_addr(vars->texture[4].img, &vars->texture[4].bits_per_pixel, &vars->texture[4].line_length, &vars->texture[4].endian);

	vars->texture[5].img = mlx_xpm_file_to_image(vars->mlx, "images/mossy.xpm", &img_width, &img_height);
	vars->texture[5].addr = mlx_get_data_addr(vars->texture[5].img, &vars->texture[5].bits_per_pixel, &vars->texture[5].line_length, &vars->texture[5].endian);

	vars->texture[6].img = mlx_xpm_file_to_image(vars->mlx, "images/wood.xpm", &img_width, &img_height);
	vars->texture[6].addr = mlx_get_data_addr(vars->texture[6].img, &vars->texture[6].bits_per_pixel, &vars->texture[6].line_length, &vars->texture[6].endian);

	vars->texture[7].img = mlx_xpm_file_to_image(vars->mlx, "images/colorstone.xpm", &img_width, &img_height);
	vars->texture[7].addr = mlx_get_data_addr(vars->texture[7].img, &vars->texture[7].bits_per_pixel, &vars->texture[7].line_length, &vars->texture[7].endian);
}

void set_direction(t_vars *vars, char dir)
{
	if (dir == 'N')
	{
		//initial direction vector
		vars->dirX = -1;
		vars->dirY = 0; 
		//the 2d raycaster version of camera plane
		vars->planeX = 0;
		vars->planeY = 0.66; 
	}
	else if (dir == 'S')
	{
		//initial direction vector
		vars->dirX = 1;
		vars->dirY = 0; 
		//the 2d raycaster version of camera plane
		vars->planeX = 0;
		vars->planeY = -0.66; 
	}
	else if (dir == 'E')
	{
		//initial direction vector
		vars->dirX = 0;
		vars->dirY = 1; 
		//the 2d raycaster version of camera plane
		vars->planeX = 0.66;
		vars->planeY = 0; 
	}
	else if (dir == 'W')
	{
		//initial direction vector
		vars->dirX = 0;
		vars->dirY = -1; 
		//the 2d raycaster version of camera plane
		vars->planeX = -0.66;
		vars->planeY = 0; 
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	// if (argc != 2 || ft_strrchr(argv[1], '.') == NULL || ft_strncmp(
	// 		ft_strrchr(argv[1], '.'), ".cub", ft_strlen(argv[1])) != 0)
	// {
	// 	ft_putendl_fd("Error\nProgram usage : ./cub3d <map_path>.cub", 2);
	// 	exit(1);
	// }
	init_vars_struct(&vars);
	// vars.map = read_map(argv[1]);
	// check_map(&vars);
	
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		close_program(&vars);
	vars.win = mlx_new_window(vars.mlx, screenWidth,
			screenHeight, "cub3d");
	if (vars.win == NULL)
		close_program(&vars);
	// load_images(&vars);
	// draw_map(&vars);


	vars.img1.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
	vars.img1.addr = mlx_get_data_addr(vars.img1.img, &vars.img1.bits_per_pixel, &vars.img1.line_length, &vars.img1.endian);

	vars.img2.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
	vars.img2.addr = mlx_get_data_addr(vars.img2.img, &vars.img2.bits_per_pixel, &vars.img2.line_length, &vars.img2.endian);
	
	//x and y start position
	vars.posX = 2;
	vars.posY = 4;  

	set_direction(&vars, 'E');
	
	vars.moveSpeed = 0.11; //the constant value is in squares/second
	vars.rotSpeed = 0.11; //the constant value is in radians/second

	vars.ceiling_color = 0x00D1FBFF;
	vars.floor_color = 0x00A06528;

	load_images(&vars);
	// // Uint32 buffer[screenHeight][screenWidth]; // y-coordinate first because it works per scanline
	// t_data *texture[8];
	// for(int i = 0; i < 8; i++) 
	// 	texture[i] = malloc(sizeof(int) * (texWidth * texHeight)); //PROTECT AND FREE

	// //generate some textures
	// for(int x = 0; x < texWidth; x++)
	// for(int y = 0; y < texHeight; y++)
	// {
	// 	int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
	// 	//int xcolor = x * 256 / texWidth;
	// 	int ycolor = y * 256 / texHeight;
	// 	int xycolor = y * 128 / texHeight + x * 128 / texWidth;
	// 	texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
	// 	texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
	// 	texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
	// 	texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
	// 	texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
	// 	texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
	// 	texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
	// 	texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	// }
	// vars.texture = texture;
	
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, 33, 1L << 5, close_program, &vars);
	mlx_loop_hook(vars.mlx, raycasting, &vars);
	mlx_loop(vars.mlx);
	// free_vars(&vars);
}