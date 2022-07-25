/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 07:00:39 by asimon            #+#    #+#             */
/*   Updated: 2022/07/25 13:13:32 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

# define X 1
# define Y 0



int	set_map_tab_pos(t_pars *data, char c, int *x, int y)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (data->start_pos[Y_START] != -1)
			return (ERROR);
		data->start_pos[Y_START] = y;
		data->start_pos[X_START] = *x;
		data->orient = c;
		return (1);
	}
	else if (c == ' ')
		return (2);
	else if (c == '\t')
		return (ERROR);
	else if (c == '\0' || c == '\n')
		return (2);
	return (ERROR);
}

int	set_map_tab(t_pars *data)
{
	int			i[2];
	t_lines		*buff;

	i[X] = -1;
	i[Y] = 0;
	buff = data->map_data->lines;
	while (buff && buff->line != NULL)
	{
		while (++i[X] < data->map_data->size_x )
			if (i[X] > ft_strlen(buff->line))
				data->tab[i[Y]][i[X]] = 2;
			else if (buff->line[i[X]] == '1')
				data->tab[i[Y]][i[X]] = 1;
			else if (buff->line[i[X]] == '0')
				data->tab[i[Y]][i[X]] = 0;
			else if (!ft_isdigit(buff->line[i[X]]))
				data->tab[i[Y]][i[X]] = set_map_tab_pos(data, buff->line[i[X]], &i[X], i[Y]);
			else
				return (ft_error("Error\nInvalid map\n"));
		i[X] = -1;
		i[Y]++;
		buff = buff->next;
	}
	return (SUCCESS);
}

int	check_data_map(t_pars *data, int x, int y)
{
	if ((x == 0 || y == 0) && data->tab[y][x] == 0)
		return (1);
	else if (y == data->map_data->size_y -1 && data->tab[y][x] == 1)
		return (0);
	else if (x == data->map_data->size_x - 1 && data->tab[y][x] == 1)
		return (0);
	else if ((y == data->map_data->size_y - 1) && data->tab[y][x] == 0)
		return (1);
	else if ((x == data->map_data->size_x - 1) && data->tab[y][x] == 0)
		return(1);
	else if (data->tab[y][x] == 0 && (data->tab[y][x + 1] == 2 || data->tab[y][x - 1] == 2))
		return (1);
	else if (data->tab[y][x] == 0 && (data->tab[y - 1][x] == 2 || data->tab[y + 1][x] == 2))
		return (1);
	return (0);
}

int	check_map(t_pars *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < data->map_data->size_y)
	{
		while (x < data->map_data->size_x)
		{
			if (data->tab[y][x] == -1 || check_data_map(data, x, y))
				return (ERROR);
			x++;
		}
		x = 0;
		y++;
	}
	return (SUCCESS);
}

void	parse_map(t_pars *data, int fd)
{
	t_map_data	map_data;
	int			ret;

	ret = 0;
	data->map_data = &map_data;
	init_map_data(&map_data);
	ret = get_tab_start(fd, &map_data);
	if (ret != ERROR)
		ret = get_tab_size_x(fd, &map_data);	
	if (ret != ERROR)
		ret = get_tab_size_y(&map_data);
	if (ret != ERROR)
		init_map_tab(&map_data, data);
	if (ret != ERROR)
		ret = set_map_tab(data);
	if (ret != ERROR)
		ret = check_map(data);
	if (ret == ERROR || map_data.size_x < 3
		|| map_data.size_y < 3 || data->start_pos[Y_START] == -1)
	{
		ft_error("Error\nInvald map\n");
		free_data_pars(data);
	}
}