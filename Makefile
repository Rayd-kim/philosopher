
NAME = philo

CC = gcc -Wall -Werror -Wextra

FILE = time.c philosopher.c make_struct.c philo_utils.c

OBJS = $(FILE:.c=.o)

all : $(NAME)

%.o : %.c 
	$(CC) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re
