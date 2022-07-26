/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 02:26:55 by asimon            #+#    #+#             */
/*   Updated: 2022/07/26 15:19:01 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

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
		ft_error("Error\nInvalid map\n");
	free_map_data(&map_data);
	close(fd);
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
		else if (check_text_data(&obj, data) > 0 )
			obj.stop_cond += 1;
		else if (obj.line && obj.split_line[0])
			obj.stop_cond = STOP_COND_ERROR;
		free(obj.line);
		if (obj.stop_cond >= 0)
			obj.line = get_next_line(fd);
		free_split_line(obj.split_line);
	}
	if (obj.line != NULL && obj.stop_cond > 0)
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
	parse_map(data, 3);
	return (data);
}
