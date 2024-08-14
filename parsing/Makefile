NAME	=	minishell
FILES	=	minishell.c lexer.c utils.c tokenize.c
LIBFT	=	libft.a
FLAGS	=	-lreadline # -Wall -Wextra -Werror
OBJS	=	$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@gcc $(FLAGS) -o $(NAME) $(OBJS) libft/$(LIBFT) -lreadline

%.o: %.c
	@gcc $(FLAGS) -c $<

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
