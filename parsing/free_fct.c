/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:31:56 by asimon            #+#    #+#             */
/*   Updated: 2022/07/25 17:51:45 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

int	free_split_line(char **split_line)
{
	int		i;

	i = 0;
	if (split_line == NULL)
		return (STOP_COND_ERROR);
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
	return (STOP_COND_ERROR);
}

void	free_data_pars(t_pars *data)
{
	size_t		y;

	y = 0;
	if (data == NULL)
		return ;
	if (data->n_tpath)
		free(data->n_tpath);
	if (data->e_tpath)
		free(data->e_tpath);
	if (data->s_tpath)
		free(data->s_tpath);
	if (data->w_tpath)
		free(data->w_tpath);
	if (data->tab != NULL)
	{
		while (y < data->tab_size)
			free(data->tab[y++]);
		free(data->tab);
	}
	free(data);
}

void	free_map_data(t_map_data *map_data)
{
	t_lines		*buff;

	if (map_data->lines != NULL)
	{
		while (map_data->lines)
		{
			if (map_data->lines->line != NULL)
				free(map_data->lines->line);
			buff = map_data->lines->next;
			free(map_data->lines);
			map_data->lines = buff;
		}
	}
}
