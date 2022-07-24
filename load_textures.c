/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:58:59 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/24 15:46:55 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Load the texture images for the game assets from the .xpm files*/
void	load_textures(t_vars *vars)
{
	int		img_width;
	int		img_height;

	vars->texture[0].img = mlx_xpm_file_to_image(vars->mlx, "images/greystone.xpm", &img_width, &img_height);
	if (vars->texture[0].img == NULL)
		close_program(vars, 1);
	vars->texture[0].addr = mlx_get_data_addr(vars->texture[0].img, &vars->texture[0].bits_per_pixel, &vars->texture[0].line_length, &vars->texture[0].endian);
	if (vars->texture[0].addr == NULL)
		close_program(vars, 1);
	vars->texture[1].img = mlx_xpm_file_to_image(vars->mlx, "images/redbrick.xpm", &img_width, &img_height);
	if (vars->texture[1].img == NULL)
		close_program(vars, 1);
	vars->texture[1].addr = mlx_get_data_addr(vars->texture[1].img, &vars->texture[1].bits_per_pixel, &vars->texture[1].line_length, &vars->texture[1].endian);
	if (vars->texture[1].addr == NULL)
		close_program(vars, 1);
	vars->texture[2].img = mlx_xpm_file_to_image(vars->mlx, "images/colorstone.xpm", &img_width, &img_height);
	if (vars->texture[2].img == NULL)
		close_program(vars, 1);
	vars->texture[2].addr = mlx_get_data_addr(vars->texture[2].img, &vars->texture[2].bits_per_pixel, &vars->texture[2].line_length, &vars->texture[2].endian);
	if (vars->texture[2].addr == NULL)
		close_program(vars, 1);
	vars->texture[3].img = mlx_xpm_file_to_image(vars->mlx, "images/wood.xpm", &img_width, &img_height);
	if (vars->texture[3].img == NULL)
		close_program(vars, 1);
	vars->texture[3].addr = mlx_get_data_addr(vars->texture[3].img, &vars->texture[3].bits_per_pixel, &vars->texture[3].line_length, &vars->texture[3].endian);
	if (vars->texture[3].addr == NULL)
		close_program(vars, 1);
}
