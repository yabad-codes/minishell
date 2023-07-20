/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:43:58 by yabad             #+#    #+#             */
/*   Updated: 2023/07/16 11:05:00 by yabad            ###   ########.fr       */
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

/**
 * @brief The starting point of execution
 * @param ast Our tree
*/
void			execute(t_ast *ast, t_ast *head, t_env **env);
char			*get_path(char *cmd);
t_builtin_type	is_builtin(char *cmd);
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
void			ft_export(t_cmd *cmd);
void			ft_unset(t_cmd *cmd, t_env **env);
void			ft_env(t_cmd *cmd, t_env *env);
void			ft_exit(t_cmd *cmd);
#endif