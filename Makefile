CC = gcc
CFLAGS = #-fsanitize=address -g
NAME = minishell
INCLUDES = ./includes

SRC = 	minishell.c \
		free.c \
		print.c \
		lexer/lexer.c \
		lexer/token_list.c \
		lexer/utils.c \
		lexer/syntax_err_utils.c \
		lexer/syntax_err.c \
		parser/parser.c \
		parser/parse_list.c \
		parser/parse_list_plus.c \
		parser/parse_cmd.c \
		parser/parser_utils.c \
		parser/exec_arg.c \
		parser/expand_variables.c \
		exec/exec.c \
		exec/handling_redirections.c \
		exec/redirection_cases.c \
		exec/error.c \
		exec/get_path.c \
		exec/builtins/builtins_call.c \
		exec/builtins/echo.c \
		exec/builtins/pwd.c \
		exec/builtins/cd.c \
		exec/builtins/env.c \
		exec/builtins/exit.c \
		exec/builtins/export.c \
		exec/builtins/unset.c \
		env/env.c \
		env/env_utils.c


HEADER = $(INCLUDES)/minishell.h
LIBFT_DIR = ./Libft
LIBFT_LIB = ./Libft/libft.a
READLINE = $(shell brew --prefix readline)
OBJS = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c $(LIBFT_LIB) $(HEADER)
	@$(CC) -I $(INCLUDES) $(CFLAGS) -I $(READLINE)/include -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(LIBFT_LIB) -L $(READLINE)/lib -lreadline $(OBJS) -o $(NAME)

$(LIBFT_LIB):
	@$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re