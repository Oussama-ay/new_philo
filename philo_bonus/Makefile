# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 09:24:17 by oayyoub           #+#    #+#              #
#    Updated: 2025/02/15 08:31:41 by oayyoub          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = dining_bonus.c dining_utils_bonus.c input_bonus.c monitoring_bonus.c philo_bonus.c time_bonus.c
OBJ = ${SRC:.c=.o}

NAME = philo_bonus

all: ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME} 

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: ${OBJ}
