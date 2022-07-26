/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 02:27:19 by asimon            #+#    #+#             */
/*   Updated: 2022/07/26 14:03:21 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../cub3d.h"
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 1
# define ERROR -1
# define SUCCESS 1
# define STOP_COND_ERROR -6
# define CHECK 0
# define MAX_VALUE 1
# define Y_START 0 // for data->start_pos
# define X_START 1

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

typedef struct s_parsing
{
	int				**tab;
	size_t			tab_size;
	char			*n_tpath;
	char			*s_tpath;
	char			*w_tpath;
	char			*e_tpath;
	int				start_pos[2];
	char			orient;
	int				fcolor[3];
	int				ccolor[3];
	t_map_data		*map_data;
}	t_pars;

typedef struct s_check_data
{
	char	*line;
	char	**split_line;
	int		stop_cond;
}	t_check_data;

// Parsing
t_pars		*parsing(char *arg);

// Data
int			set_pars_fc(char *line, int tab[]);
int			set_pars_text(char **split_line, char **str);
void		parse_map(t_pars *data, int fd);
int			check_data(const int fd, t_pars *data);

// Map
int			set_map_tab_pos(t_pars *data, char c, int *x, int y);
int			check_map(t_pars *data);
int			set_map_tab(t_pars *data);
int			check_data_map(t_pars *data, size_t x, size_t y);

// Utils - data
int			open_file(char *path);
int			is_wspace(char c);
int			ft_error(char *str);

// Utils - map
int			should_inmap(char *c);
void		add_lines(t_lines *line, t_lines *old_line);
int			get_tab_size_x(int fd, t_map_data *map_data);
int			get_tab_size_y(t_map_data *map_data);
int			get_tab_start(int fd, t_map_data *map_data);

// Init
void		init_data_pars(t_pars *data);
void		init_obj_check(t_check_data *obj, int fd);
void		init_map_data(t_map_data *map_data);
void		init_map_tab(t_map_data *map_data, t_pars *data);
t_lines		*init_lines(void);

// free
void		free_map_data(t_map_data *map_data);
int			free_split_line(char **split_line);
void		free_data_pars(t_pars *data);

// +
char		**ft_split_wspace(char *str);

#endif
