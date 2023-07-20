/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:55:18 by yabad             #+#    #+#             */
/*   Updated: 2023/07/16 11:04:38 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtin(t_cmd *cmd, t_builtin_type kind, t_env **env)
{
	if (kind == ECHO)
		ft_echo(cmd);
	else if (kind == CD)
		ft_cd(cmd, env);
	else if (kind == PWD)
		ft_pwd();
	else if (kind == EXPORT)
		ft_export(cmd);
	else if (kind == UNSET)
		ft_unset(cmd, env);
	else if (kind == ENV)
		ft_env(cmd, *env);
	else
		ft_exit(cmd);
}

t_builtin_type	is_builtin(char *cmd)
{
	size_t	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", cmd_len))
		return (ECHO);
	else if (!ft_strncmp(cmd, "cd", cmd_len))
		return (CD);
	else if (!ft_strncmp(cmd, "pwd", cmd_len))
		return (PWD);
	else if (!ft_strncmp(cmd, "export", cmd_len))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "unset", cmd_len))
		return (UNSET);
	else if (!ft_strncmp(cmd, "env", cmd_len))
		return (ENV);
	else if (!ft_strncmp(cmd, "exit", cmd_len))
		return (EXIT);
	return (NOT_BUILTIN);
}
