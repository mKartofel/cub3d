/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:01:34 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/25 11:50:03 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculate where exactly the wall was hit (and from which
 * direction) and then find the approriate texture to draw and which vertical
 * stripe (tex_x) of the texture should be drawn.
 * 
 * @param vars 
 * @param ray 
 */
void	find_texture_to_draw(t_vars *vars, t_ray *ray)
{
	if (ray->side == 'N' || ray->side == 'S')
		ray->wallx = vars->posy + ray->perpwalldist * ray->raydiry;
	else
		ray->wallx = vars->posx + ray->perpwalldist * ray->raydirx;
	ray->wallx -= floor((ray->wallx));
	if (ray->side == 'N')
		ray->tex_num = 0;
	else if (ray->side == 'S')
		ray->tex_num = 1;
	else if (ray->side == 'E')
		ray->tex_num = 2;
	else if (ray->side == 'W')
		ray->tex_num = 3;
	ray->tex_x = (int)(ray->wallx
			* (double)vars->texture[ray->tex_num].img_width);
	if ((ray->side == 'N' || ray->side == 'S') && ray->raydirx > 0)
		ray->tex_x = vars->texture[ray->tex_num].img_width - ray->tex_x - 1;
	if ((ray->side == 'E' || ray->side == 'W') && ray->raydiry < 0)
		ray->tex_x = vars->texture[ray->tex_num].img_width - ray->tex_x - 1;
}

/**
 * @brief Draw a vertical stripe of the texture on the screen.
 * The step is to calculate by how much to increase the texture coordinate
 * per screen pixel.
 * The mask with (TEXHEIGHT - 1) is to protect in case of overflow.
 * 
 * @param vars 
 * @param ray 
 */
void	draw_texture(t_vars *vars, t_ray *ray)
{
	ray->step = 1.0 * vars->texture[ray->tex_num].img_height / ray->line_height;
	ray->tex_pos = (ray->draw_start - SCREENHEIGHT / 2 + ray->line_height / 2)
		* ray->step;
	ray->y = ray->draw_start;
	while (ray->y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos
			& (vars->texture[ray->tex_num].img_height - 1);
		ray->tex_pos += ray->step;
		ray->color = get_pixel_color(&vars->texture[ray->tex_num], ray->tex_x,
				ray->tex_y);
		custom_mlx_pixel_put(vars, vars->x, ray->y, ray->color);
		ray->y++;
	}
}
