/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 07:00:39 by asimon            #+#    #+#             */
/*   Updated: 2022/07/25 03:50:36 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

int	get_tab_start(int fd, t_map_data *map_data)
{
	char	*line;
	char	**split_line;

	line = get_next_line(fd);
	if (line == NULL)
		return (ERROR);
	split_line = ft_split_wspace(line);
	while (line != NULL && split_line[0] == NULL)
	{
		free(line);
		free_split_line(split_line);
		line = get_next_line(fd);
		split_line = ft_split_wspace(line);
	}
	if (line == NULL)
		return (ERROR);
	map_data->lines->line = line;
	free(split_line);
	return (SUCCESS);
}


void	parse_map(t_pars *data, int fd)
{
	t_map_data	map_data;
	// verifier que les lignes sont bien ferme
	// recuperation de

	init_map_data(&map_data);
	get_tab_start(fd, &map_data);
	if (get_tab_size_x(fd, &map_data) == ERROR)	
		ft_error("Error\ninvalid map\n");
	if (get_tab_size_y(&map_data) == ERROR)
		ft_error("Error\nInvalid map\n");
	init_map_tab(&map_data, data);
	printf("tab_size x: |%zu|\ntab_size y: |%zu|\n", map_data.size_x, map_data.size_y);
}