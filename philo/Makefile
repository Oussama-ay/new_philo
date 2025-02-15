# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 09:24:17 by oayyoub           #+#    #+#              #
#    Updated: 2025/02/14 09:25:40 by oayyoub          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = dining.c dining_utils.c input.c monitoring.c philo.c time.c
OBJ = ${SRC:.c=.o}

NAME = philo

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
