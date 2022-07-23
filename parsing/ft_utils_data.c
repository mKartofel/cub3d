/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:38:31 by asimon            #+#    #+#             */
/*   Updated: 2022/07/23 05:59:48 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

int	open_file(char *path)
{
	int		ret;
	char	*buff;

	buff = ft_strrchr(path, '.');
	if (ft_strncmp(buff, ".cub", 4) != 0)
		return (ft_error("Error\nmap format must be [[name].cub]\n"));
	ret = open(path, O_RDONLY);
	if (ret < 0)
	{
		perror(path);
		return (ERROR);
	}
	else
		return (ret);
	return (ERROR);
}

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
	// rajouter le free du tab quand initialise
	if (data->n_tpath)
		free(data->n_tpath);
	if (data->e_tpath)
		free(data->e_tpath);
	if (data->s_tpath)
		free(data->s_tpath);
	if (data->w_tpath)
		free(data->w_tpath);
	free(data);
}

int	ft_error(char *str)
{
	if (!str)
		return (0);
	write(2, str, ft_strlen(str));
	return (ERROR);
}

int	is_wspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
