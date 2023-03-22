SRCS	= $(wildcard ./philos/*.c)

BONUS_SRCS	= $(wildcard ./philos_bonus/*.c)

CC		= cc

CFLAGS	= -Werror -Wextra -Wall -fsanitize=address -g

NAME	= philo

BONUS_NAME	= philos_bonus

OBJS	= $(SRCS:.c=.o)

OBJS_BONUS	= $(BONUS_SRCS:.c=.o)

MK_FILE	= Makefile

PTHREAD	= -lpthread

.c.o	:
			$(CC) $(CFLAGS) -o $@ -c $<

all		: $(NAME)

$(NAME)	: $(OBJS) $(MK_FILE)
		$(CC) $(CFLAGS) $(PTHREAD) $(SRCS) -o $(NAME)

bonus	: $(BONUS_NAME)

$(BONUS_NAME) : $(BONUS_OBJS) $(MK_FILE)
		$(CC) $(CFLAGS) $(PTHREAD) $(BONUS_SRCS) -o $(BONUS_NAME)

clean	:
		rm -rf $(OBJS) $(BONUS_OBJS)

fclean	: clean
		rm -rf $(NAME) $(BONUS_NAME)

re		: fclean all