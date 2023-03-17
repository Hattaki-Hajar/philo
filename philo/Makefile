SRCS	= $(wildcard *.c)

CC		= cc

CFLAGS	= -Werror -Wextra -Wall -fsanitize=thread -g

NAME	= philo

OBJS	= $(SRCS:.c=.o)

MK_FILE	= Makefile

PTHREAD	= -lpthread

.c.o	:
			$(CC) $(CFLAGS) -o $@ -c $<

all		: $(NAME)

$(NAME)	: $(OBJS) $(MK_FILE)
		$(CC) $(CFLAGS) $(PTHREAD) $(SRCS) -o $(NAME)

clean	:
		rm -rf $(OBJS)

fclean	: clean
		rm -rf $(NAME)
		echo $(NAME) is deleted

re		: fclean all