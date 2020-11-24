CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= main.c binary_diff.c
OBJS	= $(SRCS:.c=.o)
NAME	= diff_bin
RM		= rm -rf

all	:	$(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re	:	fclean all

.PHONY	: all clean fclean re
