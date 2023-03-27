SRCS	= $(wildcard *.c) ../philo/utils.c ../philo/utils2.c

CC		= cc

CFLAGS	= -Werror -Wextra -Wall

NAME	= philo_bonus

OBJS	= $(SRCS:.c=.o)

MK_FILE	= Makefile

PTHREAD	= -lpthread

.c.o	:
			$(CC) $(CFLAGS) -o $@ -c $<

all		: $(NAME)

$(NAME) : $(OBJS) $(MK_FILE)
		$(CC) $(CFLAGS) $(PTHREAD) $(SRCS) -o $(NAME)

clean	:
		rm -rf $(OBJS)

fclean	: clean
		rm -rf $(NAME)

re		: fclean all