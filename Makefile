CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
INCLUDES = ./includes

SRC = minishell.c lexer/*.c

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