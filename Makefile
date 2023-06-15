# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 17:42:21 by acarlott          #+#    #+#              #
#    Updated: 2023/06/13 14:34:10 by acarlott         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread -o2
CC = cc
HEADER = ./include

SRCS =	core/main.c \
		core/philo_exec.c \
		core/parsing.c \
		core/philo_life.c \
		core/philo_init.c \
		core/philo_utils.c \
		utils/ft_isdigit.c \
		core/fork_manager.c \
		core/time_manager.c \
		utils/ft_atoi.c \

OBJS = ${SRCS:.c=.o}

./core/%.o:	./core/%.c Makefile ${HEADER}/philo.h
	${CC} ${CFLAGS} -I ${HEADER} -g -c $< -o $@ 

all : ${NAME}

${NAME} : ${OBJS}
	echo "\033[1;34m\nCreate: \033[1;33mphilo"
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	echo "\033[1;32mSucces !\n"

force :

clean :
	echo "\033[1;31m\nClean: \033[1;36mAll *.o"
	${RM} ${OBJS}
	echo "\033[1;32mDelete !\n"

fclean: clean
	echo "\033[1;31mClean: \033[1;36mAll *.a && executable"
	${RM} ${NAME}
	echo "\033[1;32mDelete !\n"

re : fclean all


.PHONY: all clean fclean re force
