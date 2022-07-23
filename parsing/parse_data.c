/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:06:29 by asimon            #+#    #+#             */
/*   Updated: 2022/07/23 03:17:13 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

char	**set_new_split_line(char *line)
{
	char	**ret;
	char	*buff;
	char	*mod;
	int		i;

	i = 0;
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
	while (ret[i] != NULL)
	{
		buff = ret[i];
		ret[i] = ft_strtrim(ret[i], " \n\t\n\r\v");
		free(buff);
		i++;
	}
	return (ret);
}

static int	set_nu(char *str)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9') && str[i] != ',')
	{
		ret = (ret * 10) + (str[i] - 48);
		i++;
	}
	if (ret > 255 || ret < 0)
		return (ft_error("Error\ncolor out of range\n"));
	if (str[i] != ',' && str[i] != '\0')
		return (ft_error("Error\nWrong format for [floor/ceileing]'s color"));
	return (ret);
}

int	set_pars_fc(char *line, int tab[])
{
	char	**new_split_line;
	char	*buff;
	int		i;
	int		check;

	i = 0;
	check = -1;
	new_split_line = set_new_split_line(line);
	while (new_split_line[i] != NULL)
	{
		buff = new_split_line[i];
		if (!new_split_line[i])
			return (STOP_COND_ERROR);
		while (new_split_line[i][++check] != '\0')
			if (!ft_isdigit(new_split_line[i][check]))
			{
				free_split_line(new_split_line);
				return (STOP_COND_ERROR);
			}
		check = -1;
		tab[i] = set_nu(new_split_line[i]);
		i++;
	}
	free_split_line(new_split_line);
	return (1);
}

int	set_pars_text(char **split_line, char **str)
{
	if (split_line[1] == NULL)
		return (STOP_COND_ERROR);
	if (ft_strlen(split_line[1]) == 0)
	{
		ft_error("Error\nno path for [NO/SO/EA/WE]\n");
		return (STOP_COND_ERROR);
	}
	if (split_line[2] != NULL)
	{
		ft_error("error\nto much argument for [NO/SO/EA/WE] - needed one only\n");
		return (STOP_COND_ERROR);
	}
	if (access(split_line[1], R_OK) != 0)
	{
		ft_error("Error\n");
		perror(split_line[1]);
		return (STOP_COND_ERROR);
	}
	if (*str != NULL)
		return (ft_error("Error\nFiled allready assigned\n ") + STOP_COND_ERROR);
	*str = (char*)malloc(sizeof(char) * (ft_strlen(split_line[1]) + 1));
	if (str == NULL)
		return (STOP_COND_ERROR);
	ft_strlcpy(*str, split_line[1], ft_strlen(split_line[1]));
	return (1);
}
