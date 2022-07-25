# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 18:10:03 by vfiszbin          #+#    #+#              #
#    Updated: 2022/07/25 11:45:14 by vfiszbin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_A = ./libft/libft.a

NAME = cub3d

SRCS =	cub3d.c\
		raycasting.c\
		raycasting_textures.c\
		key_hook.c\
		draw.c\
		load_textures.c\
		init.c\
		player_movement.c\
		camera_rotation.c\
		utils.c\

OBJS = ${SRCS:.c=.o}

INCLUDES = cub3d.h

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g

LIBS = -L ./mlx -lmlx -L/usr/X11/include/../lib -lXext -lX11 -lm

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
	${RM} *.o

fclean: clean
	${MAKE} fclean -C ./libft
	${RM} *.o
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re