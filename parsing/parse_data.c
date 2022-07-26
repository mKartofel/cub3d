/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:06:29 by asimon            #+#    #+#             */
/*   Updated: 2022/07/26 14:02:49 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

char	**set_new_split_line(char *line)
{
	char	**ret;
	char	*buff;
	char	*mod;
	int		i;

	i = -1;
	ret = ft_split(line, ',');
	if (!ret || !ret[0])
		return (NULL);
	buff = ret[0];
	ret[0] = ft_strtrim(ret[0], " \n\t\n\r\v");
	free(buff);
	buff = ret[0];
	mod = malloc(sizeof(char) * (ft_strlen(&ret[0][1]) + 1));
	ft_strlcpy(mod, &ret[0][1], ft_strlen(&ret[0][1]) + 1);
	ret[0] = mod;
	free(buff);
	while (ret[++i] != NULL)
	{
		buff = ret[i];
		ret[i] = ft_strtrim(ret[i], " \n\t\n\r\v");
		free(buff);
	}
	return (ret);
}

static int	set_nu(char *str)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	if (str == NULL || str[0] == '\0')
		return (STOP_COND_ERROR);
	while (str[i] && (str[i] >= '0' && str[i] <= '9') && str[i] != ',')
	{
		ret = (ret * 10) + (str[i] - 48);
		i++;
	}
	if (ret > 255 || ret < 0)
		return (ERROR);
	if (str[i] != ',' && str[i] != '\0')
		return (ERROR);
	return (ret);
}

int	set_pars_fc(char *line, int tab[])
{
	char	**new_split_line;
	int		i;
	int		check;

	i = -1;
	check = -1;
	new_split_line = set_new_split_line(line);
	while (new_split_line[++i] != NULL)
	{
		if (!new_split_line[i])
			return (STOP_COND_ERROR);
		while (new_split_line[i][++check] != '\0')
			if (!ft_isdigit(new_split_line[i][check]))
				return (free_split_line(new_split_line));
		check = -1;
		tab[i] = set_nu(new_split_line[i]);
		if (tab[i] < 0)
			return (free_split_line(new_split_line));
	}
	free_split_line(new_split_line);
	if (i != 3)
		return (STOP_COND_ERROR);
	return (1);
}

int	set_pars_text(char **split_line, char **str)
{
	if (split_line[1] == NULL)
		return (STOP_COND_ERROR);
	if (ft_strlen(split_line[1]) == 0)
		return (STOP_COND_ERROR);
	if (split_line[2] != NULL)
		return (STOP_COND_ERROR);
	if (access(split_line[1], R_OK) != 0)
	{
		perror(split_line[1]);
		return (STOP_COND_ERROR);
	}
	if (*str != NULL)
		return (STOP_COND_ERROR);
	*str = (char *)malloc(sizeof(char) * (ft_strlen(split_line[1]) + 1));
	if (str == NULL)
		return (STOP_COND_ERROR);
	ft_strlcpy(*str, split_line[1], ft_strlen(split_line[1]));
	return (1);
}
