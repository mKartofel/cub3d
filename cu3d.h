/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cu3d.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:07:05 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/28 16:00:28 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>

#include <time.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double moveSpeed;
	double rotSpeed;
	t_data img1;
	t_data img2;
	int ceiling_color;
	int floor_color;
	t_data texture[8];
}	t_vars;

#endif