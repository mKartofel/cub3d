/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:58:59 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/26 13:35:18 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures2(t_vars *vars)
{
	vars->texture[2].img = mlx_xpm_file_to_image(vars->mlx,
			vars->pars->w_tpath, &(vars->texture[2].img_width),
			&(vars->texture[2].img_height));
	if (vars->texture[2].img == NULL)
		close_program(vars, 1);
	vars->texture[2].addr = mlx_get_data_addr(vars->texture[2].img,
			&vars->texture[2].bits_per_pixel, &vars->texture[2].line_length,
			&vars->texture[2].endian);
	if (vars->texture[2].addr == NULL)
		close_program(vars, 1);
	vars->texture[3].img = mlx_xpm_file_to_image(vars->mlx,
			vars->pars->e_tpath, &(vars->texture[3].img_width),
			&(vars->texture[3].img_height));
	if (vars->texture[3].img == NULL)
		close_program(vars, 1);
	vars->texture[3].addr = mlx_get_data_addr(vars->texture[3].img,
			&vars->texture[3].bits_per_pixel, &vars->texture[3].line_length,
			&vars->texture[3].endian);
	if (vars->texture[3].addr == NULL)
		close_program(vars, 1);
}

/*Load the texture images for the game assets from the .xpm files*/
void	load_textures(t_vars *vars)
{
	printf("HERE\n");
	printf("%s\n",vars->pars->n_tpath);
	printf("%s\n",vars->pars->s_tpath);
	vars->texture[0].img = mlx_xpm_file_to_image(vars->mlx,
			vars->pars->n_tpath, &(vars->texture[0].img_width),
			&(vars->texture[0].img_height));
	if (vars->texture[0].img == NULL)
		close_program(vars, 1);
	vars->texture[0].addr = mlx_get_data_addr(vars->texture[0].img,
			&vars->texture[0].bits_per_pixel, &vars->texture[0].line_length,
			&vars->texture[0].endian);
	if (vars->texture[0].addr == NULL)
		close_program(vars, 1);
	vars->texture[1].img = mlx_xpm_file_to_image(vars->mlx,
			vars->pars->s_tpath, &(vars->texture[1].img_width),
			&(vars->texture[1].img_height));
	if (vars->texture[1].img == NULL)
		close_program(vars, 1);
	vars->texture[1].addr = mlx_get_data_addr(vars->texture[1].img,
			&vars->texture[1].bits_per_pixel, &vars->texture[1].line_length,
			&vars->texture[1].endian);
	if (vars->texture[1].addr == NULL)
		close_program(vars, 1);
	load_textures2(vars);
}
