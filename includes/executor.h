/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:43:58 by yabad             #+#    #+#             */
/*   Updated: 2023/07/18 20:15:52 by ael-maar         ###   ########.fr       */
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
void			execute(t_ast *ast, t_ast *head);
char			*get_path(char *cmd);
t_builtin_type	is_builtin(char *cmd);
void			execute_builtin(t_cmd *cmd, t_builtin_type kind);

/**
 * Builtins
*/
void			ft_echo(t_cmd *cmd);
void			ft_cd(t_cmd *cmd);
void			ft_pwd(t_cmd *cmd);
void			ft_export(t_cmd *cmd);
void			ft_unset(t_cmd *cmd);
void			ft_env(t_cmd *cmd);
void			ft_exit(t_cmd *cmd);

/**
 * Redirections
*/
void	handling_redirections(t_redir *list, t_redir_error *error);
void	out_redir(char *filename, t_redir_error *error, int *fd_out);
void	append_redir(char *filename, t_redir_error *error, int *fd_out);
void	in_redir(char *filename, t_redir_error *error, int *fd_in);
void	herdoc_redir(char *file, \
t_redir_error *error, int *fd_in);
void	error_file_message(char *filename, char *error_message);
void	handling_herdocs(t_ast *ast, int *num);
void	launch_redirections(t_redir *list, t_redir_error *error, t_fds *fds);

#endif