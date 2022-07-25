/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:41:00 by asimon            #+#    #+#             */
/*   Updated: 2022/07/25 18:10:38 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

void	init_map_data(t_map_data *map_data)
{
	map_data->lines = init_lines();
	map_data->size_x = 0;
	map_data->size_y = 0;
}

t_lines	*init_lines(void)
{
	t_lines		*ret;

	ret = malloc(sizeof(t_lines));
	if (ret == NULL)
		return (NULL);
	ret->line = NULL;
	ret->next = NULL;
	return (ret);
}

void	init_data_pars(t_pars *data)
{
	data->tab = NULL;
	data->tab_size = 0;
	data->n_tpath = NULL;
	data->s_tpath = NULL;
	data->w_tpath = NULL;
	data->e_tpath = NULL;
	data->start_pos[Y_START] = -1;
	data->start_pos[X_START] = -1;
	data->map_data = NULL;
	return ;
}

void	init_obj_check(t_check_data *obj, int fd)
{
	obj->line = get_next_line(fd);
	obj->stop_cond = 0;
}

void	init_map_tab(t_map_data *map_data, t_pars *data)
{
	size_t			i;

	i = 0;
	data->tab = (int **)malloc(sizeof(int *) * map_data->size_y);
	while (i < map_data->size_y)
	{
		data->tab[i] = (int *)malloc(sizeof(int) * map_data->size_x);
		i++;
	}
}
