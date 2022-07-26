/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:12:23 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/07/26 14:48:13 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculate ray position and direction.
 * camerax is between -1 and 1, it is a projection of the x of the real
 * screen to the x of the camera plane.
 * mapx and mapy are the coordinates of the map square the player is in.
 * delta_distx is the dist covered by the ray in dir y if we move 1 step
 * in dir x.
 * 1e30 is infinity, it is used when protecting against division by 0.
 * 
 * @param vars 
 * @param ray 
 */
void	calc_ray_pos_and_dir(t_vars *vars, t_ray *ray)
{
	ray->camerax = 2 * vars->x / (double)SCREENWIDTH - 1;
	ray->raydirx = vars->dirx + vars->planex * ray->camerax;
	ray->raydiry = vars->diry + vars->planey * ray->camerax;
	ray->mapx = (int)(vars->posx);
	ray->mapy = (int)(vars->posy);
	if (ray->raydirx == 0)
		ray->delta_distx = 1e30;
	else
		ray->delta_distx = sqrt(1 + (ray->raydiry * ray->raydiry)
				/ (ray->raydirx * ray->raydirx));
	if (ray->raydiry == 0)
		ray->delta_disty = 1e30;
	else
		ray->delta_disty = sqrt(1 + (ray->raydirx * ray->raydirx)
				/ (ray->raydiry * ray->raydiry));
	ray->hit = 0;
}

/**
 * @brief stepx is negative if the ray direction (raydir vector) has a negative
 * x value.
 * side_distx is the distance between the ray starting position and the first
 * side of the map square to the left/right.
 * 
 * @param vars 
 * @param ray 
 */
void	calc_step_and_initial_side_dist(t_vars *vars, t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->side_distx = (vars->posx - ray->mapx) * ray->delta_distx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_distx = (ray->mapx + 1.0 - vars->posx) * ray->delta_distx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->side_disty = (vars->posy - ray->mapy) * ray->delta_disty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_disty = (ray->mapy + 1.0 - vars->posy) * ray->delta_disty;
	}
}

/**
 * @brief Perform Digital Differential Analysis to find which wall square of
 * the map the ray will hit.
 * The ray is incremented by 1 square (either if the x-direction or the
 * y-direction) each time until a wall is hit.
 * When a wall is hit, we can determine from which side (N,S,E,W) it was hit.
 * 
 * @param ray 
 */
void	dda(t_vars *vars, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->mapx += ray->stepx;
			if (ray->stepx == 1)
				ray->side = 'N';
			else if (ray->stepx == -1)
				ray->side = 'S';
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->mapy += ray->stepy;
			if (ray->stepy == -1)
				ray->side = 'E';
			else if (ray->stepy == 1)
				ray->side = 'W';
		}
		if (vars->pars->tab[ray->mapx][ray->mapy] == 1)
			ray->hit = 1;
	}
}

/**
 * @brief Calculate the perpendicular (shortest) distance from the point where
 * the ray hit the wall to the camera plane to avoid the fisheye effect.
 * Then, with the distance to the wall calculated we can calculate the height
 * of the vertical line (stripe) to draw on the screen so that it represents
 * the wall according to its distance to the player.
 * draw_start and draw_end are the pixel points around the center of the screen
 * where we will start and end the vertical stripe.
 * 
 * @param vars 
 * @param ray 
 */
void	calc_perpwalldist(t_vars *vars, t_ray *ray)
{
	if (ray->side == 'N' || ray->side == 'S')
		ray->perpwalldist = (ray->mapx - vars->posx + (1 - ray->stepx) / 2)
			/ ray->raydirx;
	else
		ray->perpwalldist = (ray->mapy - vars->posy + (1 - ray->stepy) / 2)
			/ ray->raydiry;
	if (ray->perpwalldist <= 0)
		ray->perpwalldist = 0.1;
	ray->line_height = (int)(SCREENHEIGHT / ray->perpwalldist);
	ray->draw_start = (SCREENHEIGHT / 2) - (ray->line_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (SCREENHEIGHT / 2) + (ray->line_height / 2);
	if (ray->draw_end >= SCREENHEIGHT)
		ray->draw_end = SCREENHEIGHT - 1;
}

int	raycasting(t_vars *vars)
{
	t_ray	ray;

	vars->x = 0;
	while (vars->x < SCREENWIDTH)
	{
		calc_ray_pos_and_dir(vars, &ray);
		calc_step_and_initial_side_dist(vars, &ray);
		dda(vars, &ray);
		calc_perpwalldist(vars, &ray);
		find_texture_to_draw(vars, &ray);
		draw_texture(vars, &ray);
		draw_vertical_line(vars, 0, ray.draw_start, vars->ceiling_color);
		draw_vertical_line(vars, ray.draw_end, SCREENHEIGHT, vars->floor_color);
		vars->x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img1.img, 0, 0);
	player_movement(vars);
	swap_imgs(vars);
	return (0);
}
