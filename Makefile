NAME	=	minishell
FILES	=	minishell.c
LIBFT	=	libft.a
FLAGS	=	# -Wall -Wextra -Werror
OBJS	=	$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@cc $(FLAGS) -o $(NAME) $(OBJS) libft/$(LIBFT)

%.o: %.c
	@cc $(FLAGS) -c $<

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
