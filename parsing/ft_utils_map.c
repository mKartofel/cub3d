/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:25:30 by asimon            #+#    #+#             */
/*   Updated: 2022/07/26 19:49:28 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

int	should_inmap(char *c)
{
	int			ret;
	int			i;

	i = 0;
	ret = 0;
	if (!(c[i] == '1' || c[i] == '0' || c[i] == 'N' || c[i] == 'S'
			|| c[i] == 'W' || c[i] == 'E' || c[i] == ' ' || c[i] == '\t'))
		return (0);
	while (c[i])
	{
		if (c[i] != ' ')
			ret = 1;
		i++;
	}
	return (ret);
}

void	add_lines(t_lines *line, t_lines *old_line)
{
	while (old_line->next != NULL)
		old_line = old_line->next;
	old_line->next = line;
	line->next = NULL;
}

int	get_tab_size_x(int fd, t_map_data *map_data)
{
	t_lines		*buff;
	size_t		i;

	i = 0;
	buff = map_data->lines;
	if (ft_strchr(buff->line, '1') == NULL)
		return (ERROR);
	map_data->size_x = ft_strlen(buff->line);
	buff->next = init_lines();
	buff = buff->next;
	buff->line = get_next_line(fd);
	while (buff->line != NULL)
	{
		while (buff->line[i] && should_inmap(&buff->line[i]))
			i++;
		if (i > map_data->size_x)
			map_data->size_x = i;
		i = 0;
		buff->next = init_lines();
		buff = buff->next;
		buff->line = get_next_line(fd);
	}
	if (map_data->size_x == 0)
		return (ERROR);
	return (SUCCESS);
}

int	get_tab_size_y(t_map_data *map_data, t_pars *data)
{
	t_lines		*tmp_1;
	t_lines		*tmp_2;

	tmp_1 = map_data->lines;
	tmp_2 = map_data->lines;
	while (tmp_1 != NULL && tmp_1->line != NULL)
	{
		while (tmp_2 != NULL && tmp_2->line != NULL)
		{
			if (ft_strchr(tmp_2->line, '1'))
				break ;
			tmp_2 = tmp_2->next;
		}
		if (tmp_2 == NULL)
			return (SUCCESS);
		map_data->size_y++;
		data->tab_size = map_data->size_y;
		tmp_1 = tmp_1->next;
		tmp_2 = tmp_1;
	}
	return (SUCCESS);
}

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
	free_split_line(split_line);
	if (line == NULL)
		return (ERROR);
	map_data->lines->line = line;
	return (SUCCESS);
}
