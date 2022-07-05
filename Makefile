# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 15:27:06 by youskim           #+#    #+#              #
#    Updated: 2022/07/05 21:56:36 by youskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc -Wall -Werror -Wextra 
# -g -fsanitize=thread

FILE = time.c philosopher.c make_struct.c philo_utils.c

OBJS = $(FILE:.c=.o)

all : $(NAME)

%.o : %.c 
	$(CC) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean : 
	rm -rf $(OBJS)

fclean : 
	make clean
	rm -rf $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re
