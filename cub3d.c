/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:13:37 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/27 17:04:22 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cu3d.h"

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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
      if(worldMap[(int)(vars->posX + vars->dirX * vars->moveSpeed)][(int)(vars->posY)] == 0) vars->posX += vars->dirX * vars->moveSpeed;
      if(worldMap[(int)(vars->posX)][(int)(vars->posY + vars->dirY * vars->moveSpeed)] == 0) vars->posY += vars->dirY * vars->moveSpeed;
    }
    //move backwards if no wall behind you
    if(keycode == 115)
    {
      if(worldMap[(int)(vars->posX - vars->dirX * vars->moveSpeed)][(int)(vars->posY)] == 0) vars->posX -= vars->dirX * vars->moveSpeed;
      if(worldMap[(int)(vars->posX)][(int)(vars->posY - vars->dirY * vars->moveSpeed)] == 0) vars->posY -= vars->dirY * vars->moveSpeed;
    }
    //rotate to the right
    if(keycode == 100)
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
    if(keycode == 97)
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

void draw_line(t_vars *vars, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	//  pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 10
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
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
      //This can be computed as (mapX - vars->posX + (1 - stepX) / 2) / rayvars.dirX for side == 0, or same formula with Y
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

      //choose wall color
      int color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = 0x00FF0000;    break; //red
        case 2:  color = 0x0000FF00;  break; //green
        case 3:  color = 0x000000FF;   break; //blue
        case 4:  color = 0x00F7F8F6;  break; //white
        default: color = 0x00FFBB00; break; //yellow
      }

      //give x and y sides different brightness
      if(side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
	  draw_line(vars, x, drawStart, x, drawEnd, color);
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
	
	return (0);
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
	vars.posX = 22;
	vars.posY = 12;  
	//initial direction vector
	vars.dirX = -1;
	vars.dirY = 0; 
	//the 2d raycaster version of camera plane
	vars.planeX = 0;
	vars.planeY = 0.66; 

    vars.moveSpeed = 0.11; //the constant value is in squares/second
    vars.rotSpeed = 0.11; //the constant value is in radians/second
	
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win, 33, 1L << 5, close_program, &vars);
	mlx_loop_hook(vars.mlx, raycasting, &vars);
	mlx_loop(vars.mlx);
	// free_vars(&vars);
}