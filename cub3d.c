/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:13:37 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/26 14:11:14 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldmap[MAPWIDTH][MAPHEIGHT]=
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
	int	i;

	if (vars->img1.img != NULL)
		mlx_destroy_image(vars->mlx, vars->img1.img);
	if (vars->img2.img != NULL)
		mlx_destroy_image(vars->mlx, vars->img2.img);
	i = 0;
	while (i < NBTEXTURES)
	{
		if (vars->texture[i].img)
			mlx_destroy_image(vars->mlx, vars->texture[i].img);
		i++;
	}
	if (vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx != NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
}

int	close_program(t_vars *vars, int ret)
{
	if (vars->mlx)
		mlx_loop_end(vars->mlx);
	free_vars(vars);
	exit(ret);
}

int	close_red_cross(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	free_vars(vars);
	exit(0);
}

void	swap_imgs(t_vars *vars)
{
	void	*tmp;

	tmp = vars->img1.img;
	vars->img1.img = vars->img2.img;
	vars->img2.img = tmp;
	tmp = vars->img1.addr;
	vars->img1.addr = vars->img2.addr;
	vars->img2.addr = tmp;
}


int	main(int argc, char **argv)
{
	t_vars	vars;
	t_pars	*data;
	

	(void)argc;
	// if (argc != 2 || ft_strrchr(argv[1], '.') == NULL || ft_strncmp(
	// 		ft_strrchr(argv[1], '.'), ".cub", ft_strlen(argv[1])) != 0)
	// {
	// 	ft_putendl_fd("Error\nProgram usage : ./cub3d <map_path>.cub", 2);
	// 	exit(1);
	// }
	init_vars_struct(&vars);

	//read and parse map file
	data = parsing(argv[1]);
	// if (data == NULL)
	// 		Erreur de pasing finir ici
	// 		regarde la structure pour les donnees | pour start_pos utilise les macros Y_start et X_start
	(void)data;
	vars.ceiling_color = convert_rgb_to_trgb(0, 102, 204, 255);
	vars.floor_color = convert_rgb_to_trgb(0, 153, 102, 51);

	init_mlx_and_img_buffers(&vars);

	set_init_direction(&vars, 'E');

	load_textures(&vars);

	mlx_hook(vars.win, 2, 1L << 0, key_pressed_hook, &vars);
	mlx_hook(vars.win, 3, 1L << 1, key_released_hook, &vars);
	mlx_hook(vars.win, 33, 1L << 5, close_red_cross, &vars);
	mlx_loop_hook(vars.mlx, raycasting, &vars);
	mlx_loop(vars.mlx);
	free_vars(&vars);
	return (0);
}