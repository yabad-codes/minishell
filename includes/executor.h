/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:43:58 by yabad             #+#    #+#             */
/*   Updated: 2023/07/14 10:11:21 by yabad            ###   ########.fr       */
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
#endif