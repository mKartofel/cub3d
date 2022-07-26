/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:13:37 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/26 13:56:28 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_vars(t_vars *vars)
{
	int	i;

	if (vars->pars)
		free_data_pars(vars->pars);
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

	if (argc != 2 || ft_strrchr(argv[1], '.') == NULL || ft_strncmp(
			ft_strrchr(argv[1], '.'), ".cub", ft_strlen(argv[1])) != 0)
	{
		ft_putendl_fd("Error\nProgram usage : ./cub3d <map_path>.cub", 2);
		exit(1);
	}
	init_vars_struct(&vars);

	//read and parse map file
	data = parsing(argv[1]);
	if (data == NULL)
	{
		//Erreur de pasing finir ici
		exit(1);
	}
			
	// regarde la structure pour les donnees | pour start_pos utilise les macros Y_start et X_start
	// vars.ceiling_color = convert_rgb_to_trgb(0, 102, 204, 255);
	// vars.floor_color = convert_rgb_to_trgb(0, 153, 102, 51);

	vars.pars = data;
	
	vars.ceiling_color = convert_rgb_to_trgb(0, data->ccolor[0], data->ccolor[1], data->ccolor[2]);
	vars.floor_color = convert_rgb_to_trgb(0, data->fcolor[0], data->fcolor[1], data->fcolor[2]);

	////a retirer
	data->n_tpath = "./images/colorstone.xpm";
	data->s_tpath = "./images/wood.xpm";
	data->e_tpath = "./images/greystone.xpm";
	data->w_tpath = "./images/redbrick.xpm";
	////

	init_mlx_and_img_buffers(&vars);
	vars.posx = data->start_pos[0]; //x ou y ?
	vars.posy = data->start_pos[1];
	set_init_direction(&vars, data->orient);

	load_textures(&vars);

	mlx_hook(vars.win, 2, 1L << 0, key_pressed_hook, &vars);
	mlx_hook(vars.win, 3, 1L << 1, key_released_hook, &vars);
	mlx_hook(vars.win, 33, 1L << 5, close_red_cross, &vars);
	mlx_loop_hook(vars.mlx, raycasting, &vars);
	mlx_loop(vars.mlx);
	free_vars(&vars);
	return (0);
}