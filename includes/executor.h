/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:43:58 by yabad             #+#    #+#             */
/*   Updated: 2023/08/01 17:14:09 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"

typedef enum e_builtin_type
{
	NOT_BUILTIN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir_error
{
	char	*filename;
	char	*error_message;
	bool	is_error;
}	t_redir_error;

typedef struct s_fds
{
	int	fd_out;
	int	fd_in;
}	t_fds;

/**
 * @brief The starting point of execution
 * @param ast Our tree
*/
int				execute(t_ast *ast, t_ast *head, t_env **env);
char			*get_path(char *cmd, t_env *env);
t_builtin_type	is_builtin(char *cmd);
bool			is_digit(char *str);
void			execute_builtin(t_cmd *cmd, t_builtin_type kind, t_env **env);
t_env			*new_key(char *key, char *value);
void			add_key(t_env **env, t_env *new);
void			del_key(t_env *env, void (*del)(void *));

/**
 * Builtins
*/
void			ft_echo(t_cmd *cmd);
void			ft_cd(t_cmd *cmd, t_env **env);
void			ft_pwd(void);
void			ft_export(t_cmd *cmd, t_env **env);
void			ft_unset(t_cmd *cmd, t_env **env);
void			ft_env(t_cmd *cmd, t_env *env);
void			ft_exit(t_cmd *cmd);
int				ft_max(int a, int b);
bool			is_valid_identifier(char *var);

/**
 * Signals
*/

void			handle_sig(void);
void			child_handler(int sig);

/**
 * Redirections
*/
void			handling_redirections(t_redir *list, \
					t_redir *head, t_redir_error *error);
void			out_redir(char *filename, t_redir_error *error, int *fd_out);
void			append_redir(char *filename, t_redir_error *error, int *fd_out);
void			in_redir(char *filename, t_redir_error *error, int *fd_in);
void			herdoc_redir(int read_end, t_redir_error *error, int *fd_in);
void			error_file_message(char *filename, char *error_message);
void			print_error(char *cmd, char *filename, char *error_message);
void			handling_herdocs(t_ast *ast);
void			launch_redirections(t_redir *list, \
					t_redir_error *error, t_fds *fds);
void			exec_error(char *msg, t_cmd *cmd);
void			execute_cmd_child(t_cmd *cmd, t_env **env);
char			**cnv_to_envp(t_env *env);

#endif