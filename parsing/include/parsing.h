/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 02:27:19 by asimon            #+#    #+#             */
/*   Updated: 2022/07/25 03:10:02 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../cu3d.h"
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 1
# define ERROR -1
# define SUCCESS 1
# define STOP_COND_ERROR -6
# define CHECK 0
# define MAX_VALUE 1

typedef struct s_parsing
{
	int		**tab;
	char	*n_tpath;
	char	*s_tpath;
	char	*w_tpath;
	char	*e_tpath;
	int		start_pos[2];
	char	orient;
	int		fcolor[3];
	int		ccolor[3];
	char	floor;
	char	ceiling;
}	t_pars;

typedef struct s_check_data
{
	char	*line;
	char	**split_line;
	int		stop_cond;
}	t_check_data;

typedef struct s_lines
{
	char			*line;
	struct s_lines	*next;
}	t_lines;

typedef struct s_map_data
{
	t_lines	*lines;
	size_t	size_x;
	size_t	size_y;
}	t_map_data;

// Data
int			set_pars_fc(char *line, int tab[]);
int			set_pars_text(char **split_line, char **str);
void		parse_map(t_pars *data, int fd);
int			check_data(const int fd, t_pars *data);

// Map

// Utils - data
int			free_split_line(char **split_line);
void		free_data_pars(t_pars *data);
int			open_file(char *path);
int			is_wspace(char c);
int			ft_error(char *str);

// Utils - map
int			should_inmap(char *c);
void		add_lines(t_lines *line, t_lines *old_line);
int			get_tab_size_x(int fd, t_map_data *map_data);
int			get_tab_size_y(t_map_data *map_data);

// Init
void		init_data_pars(t_pars *data);
void		init_obj_check(t_check_data *obj, int fd);
void		init_map_data(t_map_data *map_data);
t_lines		*init_lines();

// +
char		**ft_split_wspace(char *str);

#endif
