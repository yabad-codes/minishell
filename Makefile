CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
INCLUDES = ./includes

SRC = 	minishell.c \
		free.c \
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
		parser/expand_variables_utils.c \
		exec/exec.c \
		exec/exec_utils.c \
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
		exec/builtins/exit_utils.c \
		exec/builtins/export.c \
		exec/builtins/unset.c \
		exec/signal.c \
		env/env.c \
		env/env_utils.c 

LIBFT_DIR = ./Libft/
LIBFT_LIB = $(LIBFT_DIR)/libft.a
READLINE = $(shell brew --prefix readline)
OBJS = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

%.o: %.c $(LIBFT_LIB)
	@$(CC) -I $(INCLUDES) $(CFLAGS) -I $(READLINE)/include/readline -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I $(READLINE)/include/readline $(OBJS) -lreadline -L $(READLINE)/lib $(LIBFT_LIB) -o $(NAME)
	@echo "\033[32mPROJECT COMPILED SUCCESSFULY\033[0m"

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
