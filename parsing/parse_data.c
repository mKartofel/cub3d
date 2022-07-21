/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:06:29 by asimon            #+#    #+#             */
/*   Updated: 2022/07/21 06:29:02 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

static int	set_nu(char *str)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9') && str[i] != ',')
	{
		ret = (ret * 10) + ft_atoi(str[i]);
		i++;
	}
	if (ret > 255 || ret < 0)
		return (ft_error("Error\ncolor out of range\n"));
	if (str[i] != ',' && str[i] != '\0')
		return (ft_error("Error\nWrong format for [floor/ceileing]'s color"));
	return (ret);
}

int	set_pars_fc(char **split_line, int tab[])
{
	int		tab_i;
	int		arg;
	int		buff;

	tab_i = 0;
	arg = 1;
	buff = 0;
	while (split_line[arg])
	{
		if (arg == 4)
			return (STOP_COND_ERROR);
		buff = set_nu(split_line[arg]);
		if (buff == ERROR)
			return (STOP_COND_ERROR);
		else
			tab[tab_i] = buff;
		arg++;
		tab_i++;
	}
	return (1);
}

int	set_pars_card_text(char **split_line, char *str)
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
	if (acces(split_line[1], R_OK) != 0)
	{
		ft_error("Error\n");
		perror(split_line[1]);
		return (STOP_COND_ERROR);
	}
	str = malloc(sizeof(char) * (ft_strlen(split_line[1]) + 1));
	if (str == NULL)
		return (STOP_COND_ERROR);
	ft_strlcpy(str, split_line[1], ft_strlen(split_line[1]));
	return (1);
}