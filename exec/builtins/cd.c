/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:42:32 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:57:29 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_env_vars(t_env **env, char buf[])
{
	modify_key(env, "OLDPWD", ft_strdup(buf));
	getcwd(buf, PATH_MAX);
	modify_key(env, "PWD", ft_strdup(buf));
}

static int	cd_home(t_env **env)
{
	char	*home;
	char	buf[PATH_MAX];

	home = get_value(*env, "HOME");
	if (!home)
	{
		error_file_message("cd", "HOME not set");
		return (1);
	}
	getcwd(buf, PATH_MAX);
	if (chdir(home))
	{
		perror("cd");
		return (1);
	}
	edit_env_vars(env, buf);
	return (0);
}

static int	cd_old(t_env **env)
{
	char	*old;
	char	buf[PATH_MAX];

	old = get_value(*env, "OLDPWD");
	if (!old)
	{
		error_file_message("cd", "OLDPWD not set");
		return (1);
	}
	getcwd(buf, PATH_MAX);
	if (chdir(old))
	{
		perror("cd");
		return (1);
	}
	edit_env_vars(env, buf);
	return (0);
}

void	ft_cd(t_cmd *cmd, t_env **env)
{
	char	buf[PATH_MAX];

	if (!cmd->cmd_args[1] || \
		!ft_strncmp("--", cmd->cmd_args[1], \
			ft_max(2, ft_strlen(cmd->cmd_args[1]))) || \
		!ft_strncmp("~", cmd->cmd_args[1], ft_strlen(cmd->cmd_args[1])))
	{
		cd_home(env);
		return ;
	}
	if (!ft_strncmp("-", cmd->cmd_args[1], ft_strlen(cmd->cmd_args[1])))
	{
		cd_old(env);
		return ;
	}
	if (!ft_strncmp(".", cmd->cmd_args[1], ft_strlen(cmd->cmd_args[1])) || \
		!ft_strncmp("..", cmd->cmd_args[1], \
			ft_max(2, ft_strlen(cmd->cmd_args[1]))))
		edit_env_vars(env, buf);
	if (chdir(cmd->cmd_args[1]))
	{
		print_error("cd", cmd->cmd_args[1], strerror(errno));
		return ;
	}
	edit_env_vars(env, buf);
}
