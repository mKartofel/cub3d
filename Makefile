# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asimon <asimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 18:10:03 by vfiszbin          #+#    #+#              #
#    Updated: 2022/07/25 18:43:20 by asimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_A 		= ./libft/libft.a

NAME 			= cub3d

C_FILE 			=	cub3d.c					\
					raycasting.c			\
					raycasting_textures.c	\
					key_hook.c				\
					draw.c					\
					load_textures.c			\
					init.c					\
					player_movement.c		\
					camera_rotation.c		\
					utils.c					\

PARSING			=	free_fct.c				\
					ft_split_wspace.c		\
					ft_utils_data.c			\
					ft_utils_map.c			\
					init_2.c				\
					parse_data.c			\
					parse_map.c				\
					parsing.c

PARSING_DIR		=	./parsing/

P_FILE			=	$(addprefix $(PARSING_DIR), $(PARSING))

SRCS			=	$(C_FILE)				\
					$(P_FILE)

OBJS 			= ${SRCS:.c=.o}

O_FILE			=	./*.o					\
					$(PARSING_DIR)*.o

INCLUDES 		= cub3d.h

CC 				= gcc

RM 				= rm -f

FLAGS 			= -Wall -Wextra -Werror -g

LIBS 			= -L ./mlx -lmlx -L/usr/X11/include/../lib -lXext -lX11 -lm

.c.o: ${INCLUDES}
	${CC} ${FLAGS} -c $ $< -o ${<:.c=.o}

all: makemlx makelibft ${NAME}

makemlx:
	${MAKE} -C ./mlx

makelibft:
	${MAKE} -C ./libft

${NAME} : ${OBJS} ${INCLUDES}
	
	${CC} ${FLAGS} ${OBJS} ${LIBFT_A} -o ${NAME} ${LIBS}

clean:
	${MAKE} clean -C ./mlx
	${MAKE} clean -C ./libft
	${RM} $(O_FILE)

fclean: clean
	${MAKE} fclean -C ./libft
	${RM} $(O_FILE)
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re