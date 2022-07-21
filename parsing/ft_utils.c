/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:38:31 by asimon            #+#    #+#             */
/*   Updated: 2022/07/21 07:08:33 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

void	free_obj_split_line(t_check_data obj)
{
	int		i;

	i = 0;
	if (obj.split_line == NULL)
		return ;
	while (obj.split_line[i])
	{
		free(obj.split_line[i]);
		i++;
	}
	free(obj.split_line);
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

int			ft_error(char *str)
{
	if (!str)
		return (0);
	write(2, str, ft_strlen(str));
	return (ERROR);
}

int			is_wspace(char c)
{
	if ((c >= 9 && c <= 13) || c ==32)
		return (1);
	return (0);
}