NAME	=	minishell

FILES	=	minishell.c \
			builtins/echo.c builtins/cd.c builtins/pwd.c \
			builtins/export.c builtins/unset.c builtins/env.c builtins/exit.c \
			execution/execution.c execution/execution_utils.c

LIBFT	=	libft/libft.a

FLAGS	=	#-Wall -Wextra -Werror

OBJS	=	$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Linking $(NAME)..."
	@cc $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@echo "$(NAME) built successfully!"

$(LIBFT):
	@echo "Building libft..."
	@make -C libft

%.o: %.c
	@echo "Compiling $<..."
	@cc $(FLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@make -C libft clean
	@rm -f $(OBJS)

fclean: clean
	@echo "Cleaning $(NAME)..."
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
