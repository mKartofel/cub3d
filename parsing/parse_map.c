/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 07:00:39 by asimon            #+#    #+#             */
/*   Updated: 2022/07/23 10:52:11 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

int	get_tab_start(int fd)
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
	free(line);
	free(split_line);
	return (1);
}

size_t	get_tab_size(int fd)
{
	int		ret;
	char	*line;

	ret = 0;
	get_tab_start(fd);
	return (ret);
}

void	parse_map(t_pars *data, int fd)
{
	int		size;  // definir la taille du tableau en premier lieu
	// verifier que les lignes sont bien ferme
	// recuperation de


	size = get_tab_size(fd);
}