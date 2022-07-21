/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 07:04:10 by asimon            #+#    #+#             */
/*   Updated: 2022/07/21 07:41:22 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

void	init_data_pars(t_pars *data)
{
	data->tab = NULL;
	data->n_tpath = NULL;
	data->s_tpath = NULL;
	data->w_tpath = NULL;
	data->e_tpath = NULL;
	return ;
}

void	init_obj_check(t_check_data *obj, int fd)
{
	obj->line = get_next_line(fd);
	obj->stop_cond = 0;
}
