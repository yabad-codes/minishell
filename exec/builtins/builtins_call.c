/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:55:18 by yabad             #+#    #+#             */
/*   Updated: 2023/07/21 10:15:09 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

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
	if (!ft_strncmp(cmd, "echo", ft_max(cmd_len, 4)))
		return (ECHO);
	else if (!ft_strncmp(cmd, "cd", ft_max(cmd_len, 2)))
		return (CD);
	else if (!ft_strncmp(cmd, "pwd", ft_max(cmd_len, 3)))
		return (PWD);
	else if (!ft_strncmp(cmd, "export", ft_max(cmd_len, 6)))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "unset", ft_max(cmd_len, 5)))
		return (UNSET);
	else if (!ft_strncmp(cmd, "env", ft_max(cmd_len, 3)))
		return (ENV);
	else if (!ft_strncmp(cmd, "exit", ft_max(cmd_len, 4)))
		return (EXIT);
	return (NOT_BUILTIN);
}
