/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 02:26:55 by asimon            #+#    #+#             */
/*   Updated: 2022/07/21 07:14:42 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

int	check_data(const int fd, t_pars *data)
{
	t_check_data	obj;

	init_obj_check(&obj, fd);
	while (obj.line != NULL && obj.stop_cond >= 0 && obj.stop_cond != 6)
	{
		obj.split_line = ft_split_wspace(obj.line);
		if (obj.split_line && ft_strncmp(obj.split_line[0], "F", 2) == 0)
			obj.stop_cond += set_pars_fc(obj.split_line, data->fcolor);
		else if (obj.split_line && ft_strncmp(obj.split_line[0], "C", 2) == 0)
			obj.stop_cond += set_pars_fc(obj.split_line, data->ccolor);
		else if (obj.split_line && ft_strncmp(obj.split_line[0], "NO", 3) == 0)
			obj.stop_cond += set_pars_card_text(obj.split_line, data->n_tpath);
		else if (obj.split_line && ft_strncmp(obj.split_line[0], "SO", 3) == 0)
			obj.stop_cond += set_pars_card_text(obj.split_line, data->s_tpath);
		else if (obj.split_line && ft_strncmp(obj.split_line[0], "WE", 3) == 0)
			obj.stop_cond += set_pars_card_text(obj.split_line, data->w_tpath);
		else if (obj.split_line && ft_strncmp(obj.split_line[0], "EA", 3) == 0)
			obj.stop_cond += set_pars_card_text(obj.split_line, data->e_tpath);
		else
			obj.stop_cond = ft_error("Error\nIncorect data identifier format\n");
		free(obj.line);
		obj.line = get_next_line(fd);
	}
	free_obj_split_line(obj);
	return (obj.stop_cond);
}

int	open_file(char *path)
{
	int		ret;

	ret = open(path, O_RDONLY);
	if (ret < 0)
	{
		perror(path);
		return (ret);
	}
	else
		return (ret);
	return (-1);
}

t_pars	*parsing(char *arg)
{
	int		fd;
	t_pars	*data;

	// check du file
	fd = open_file(arg);
	if (fd < 0)
		return (NULL);
	data = malloc(sizeof(t_pars) * 1);
	if (!data)
		return (NULL);
	if (check_data(fd, data) < 0)
	{
		ft_error("Error\nMiss some data for correct parsing\n");
		free_data_pars(data);
	}
	// check de la map
}
