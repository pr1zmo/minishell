NAME	=	minishell
FILES	=	main.c
FLAGS	=	# -Wall -Wextra -Werror
OBJS	=	$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
