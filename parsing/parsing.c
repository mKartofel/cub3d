/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 02:26:55 by asimon            #+#    #+#             */
/*   Updated: 2022/07/26 16:31:19 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

int	check_map(t_pars *data)
{
	size_t		x;
	size_t		y;

	x = 0;
	y = 0;
	data->tab_size = data->map_data->size_y;
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

int	check_text_data(t_check_data *obj, t_pars *data)
{
	if (obj->split_line && ft_strncmp(obj->split_line[0], "NO", 3) == 0)
		obj->stop_cond += set_pars_text(obj->split_line, &(data->n_tpath));
	else if (obj->split_line && ft_strncmp(obj->split_line[0], "SO", 3) == 0)
		obj->stop_cond += set_pars_text(obj->split_line, &(data->s_tpath));
	else if (obj->split_line && ft_strncmp(obj->split_line[0], "WE", 3) == 0)
		obj->stop_cond += set_pars_text(obj->split_line, &(data->w_tpath));
	else if (obj->split_line && ft_strncmp(obj->split_line[0], "EA", 3) == 0)
		obj->stop_cond += set_pars_text(obj->split_line, &(data->e_tpath));
	return (obj->stop_cond);
}

int	check_data(const int fd, t_pars *data)
{
	t_check_data	obj;

	init_obj_check(&obj, fd);
	while (obj.line != NULL && obj.stop_cond >= 0 && obj.stop_cond != 6)
	{
		obj.split_line = ft_split_wspace(obj.line);
		if (obj.split_line && obj.split_line[0]
			&& ft_strncmp(obj.split_line[0], "C", 2) == 0)
			obj.stop_cond += set_pars_fc(obj.line, data->ccolor);
		else if (obj.split_line && obj.split_line[0]
			&& ft_strncmp(obj.split_line[0], "F", 2) == 0)
			obj.stop_cond += set_pars_fc(obj.line, data->fcolor);
		else if (obj.split_line[0] && check_text_data(&obj, data) > 0)
			obj.stop_cond = obj.stop_cond;
		else if (obj.line && obj.split_line && obj.split_line[0])
			obj.stop_cond = STOP_COND_ERROR;
		free(obj.line);
		if (obj.stop_cond >= 0 && obj.stop_cond != 6)
			obj.line = get_next_line(fd);
		free_split_line(obj.split_line);
	}
	if (obj.line != NULL && obj.stop_cond > 0 && obj.stop_cond != 6)
		free(obj.line);
	return (obj.stop_cond);
}

t_pars	*parsing(char *arg)
{
	int		fd;
	t_pars	*data;

	fd = open_file(arg);
	if (fd < 0)
		return (NULL);
	data = malloc(sizeof(t_pars) * 1);
	if (!data)
		return (NULL);
	init_data_pars(data);
	if (check_data(fd, data) != 6)
	{
		ft_error("Error\nInvalid datas for correct parsing\n");
		free_data_pars(data);
		return (NULL);
	}
	if (parse_map(data, 3) == ERROR)
	{
		free_data_pars(data);
		return (NULL);
	}
	return (data);
}
