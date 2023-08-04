# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 17:42:21 by acarlott          #+#    #+#              #
#    Updated: 2023/08/04 13:12:07 by acarlott         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread -O2

CC = cc
HEADER = ./include

SRCS =	core/main.c \
		core/philo_exec.c \
		core/parsing.c \
		core/philo_life.c \
		core/philo_init.c \
		core/philo_utils.c \
		core/utils/ft_isdigit.c \
		core/fork_manager.c \
		core/time_manager.c \
		core/utils/ft_atoi.c \

OBJS = ${SRCS:.c=.o}

./core/%.o:	./core/%.c ${HEADER}/philo.h
	${CC} ${CFLAGS} -I ${HEADER} -g -c $< -o $@ 

all : ${NAME}

${NAME} : ${OBJS}
	echo "\033[1;34mCreate: \033[1;33mphilo"
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	echo "\033[1;32mSucces !"

force :

clean :
	echo "\033[1;31mClean: \033[1;36mAll *.o"
	${RM} ${OBJS}
	echo "\033[1;32mDelete !"

fclean: clean
	echo "\033[1;31mClean: \033[1;36mAll *.a && executable"
	${RM} ${NAME}
	echo "\033[1;32mDelete !"

re : fclean all

.SILENT:

.PHONY: all clean fclean re force
