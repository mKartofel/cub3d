/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 02:27:19 by asimon            #+#    #+#             */
/*   Updated: 2022/07/21 07:41:25 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../cu3d.h"
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 1
# define ERROR -1
# define STOP_COND_ERROR -6

typedef struct s_parsing
{
	int		**tab;
	char	*n_tpath;
	char	*s_tpath;
	char	*w_tpath;
	char	*e_tpath;
	int		fcolor[3];
	int		ccolor[3];
}	t_pars;

typedef struct s_check_data
{
	char	*line;
	char	**split_line;
	int		stop_cond;
}	t_check_data;

int			is_wspace(char c);
char		**ft_split_wspace(char *str);
int			set_pars_card_text(char **split_line, char *str);
int			set_pars_fc(char **split_line, int tab[]);
void		free_data_pars(t_pars *data);
void		free_obj_split_line(t_check_data obj);
void		init_data_pars(t_pars *data);
void		init_obj_check(t_check_data *obj, int fd);
int			ft_error(char *str);
int			check_data(const int fd, t_pars *data);


#endif
