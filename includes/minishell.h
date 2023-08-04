/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:02:21 by yabad             #+#    #+#             */
/*   Updated: 2023/08/01 17:02:19 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/param.h>
# include <sys/wait.h>
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "../libft/libft.h"

# define ANSI_COLOR_SKY_BLUE   "\033[1;36m"
# define ANSI_COLOR_RESET      "\x1b[0m"

typedef struct s_data
{
	t_env	*env;
	int		exit_status;
	bool	atomic;
}	t_data;

t_data	g_data;

void	rl_replace_line(const char *str, int n);
t_token	*lexer(char *input);
t_ast	*parser(t_token *tokens);

void	free_tokens_and_exit(t_token *token_head);
void	free_ast_and_exit(t_ast *ast);

t_env	*copy_env(char **envp);
char	*get_value(t_env *env, char *key);
void	modify_key(t_env **env, char *key, char *value);
void	del_key(t_env *env, void (*del)(void *));
void	add_key(t_env **env, t_env *new);
t_env	*new_key(char *key, char *value);
void	clear_env(t_env *env);

#endif
