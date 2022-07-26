/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:13:37 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/26 21:44:22 by vfiszbin         ###   ########.fr       */
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

int	close_program(t_vars *vars, int ret, char *msg)
{
	if (vars->mlx)
		mlx_loop_end(vars->mlx);
	free_vars(vars);
	if (msg)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(msg, 2);
	}
	exit(ret);
}

int	close_red_cross(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	free_vars(vars);
	exit(0);
}

void	check_args(int argc, char **argv)
{
	if (argc != 2 || ft_strrchr(argv[1], '.') == NULL || ft_strncmp(
			ft_strrchr(argv[1], '.'), ".cub", ft_strlen(argv[1])) != 0)
	{
		ft_putendl_fd("Error\nProgram usage : ./cub3d <map_path>.cub", 2);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_pars	*data;

	check_args(argc, argv);
	init_vars_struct(&vars);
	data = parsing(argv[1]);
	if (data == NULL)
		exit(1);
	vars.pars = data;
	vars.ceiling_color = convert_rgb_to_trgb(0,
			data->ccolor[0], data->ccolor[1], data->ccolor[2]);
	vars.floor_color = convert_rgb_to_trgb(0,
			data->fcolor[0], data->fcolor[1], data->fcolor[2]);
	init_mlx_and_img_buffers(&vars);
	vars.posx = data->start_pos[Y_START];
	vars.posy = data->start_pos[X_START];
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
