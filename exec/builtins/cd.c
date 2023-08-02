/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:42:32 by yabad             #+#    #+#             */
/*   Updated: 2023/07/28 08:09:00 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_env_vars(t_env **env, char buf[])
{
	modify_key(env, ft_strdup("OLDPWD"), ft_strdup(buf));
	getcwd(buf, PATH_MAX);
	modify_key(env, ft_strdup("PWD"), ft_strdup(buf));
}

static int	cd_home(t_env **env, char *env_var, char *err)
{
	char	*home;
	char	buf[PATH_MAX];

	home = get_value(*env, env_var);
	if (!home)
	{
		error_file_message("cd", err);
		return (1);
	}
	getcwd(buf, PATH_MAX);
	if (chdir(home))
	{
		perror("cd");
		return (1);
	}
	edit_env_vars(env, buf);
	if (!ft_strncmp("OLDPWD", env_var, ft_strlen(env_var)))
		printf("%s\n", buf);
	return (0);
}

void	ft_cd(t_cmd *cmd, t_env **env)
{
	char	buf[PATH_MAX];

	if (!cmd->cmd_args[1] || !ft_strncmp("--", cmd->cmd_args[1], \
			ft_max(2, ft_strlen(cmd->cmd_args[1]))) || \
		!ft_strncmp("~", cmd->cmd_args[1], ft_strlen(cmd->cmd_args[1])))
		g_data.exit_status = cd_home(env, "HOME", "HOME not set");
	else if (!ft_strncmp("-", cmd->cmd_args[1], ft_strlen(cmd->cmd_args[1])))
		g_data.exit_status = cd_home(env, "OLDPWD", "OLDPWD not set");
	else
	{
		getcwd(buf, PATH_MAX);
		if (chdir(cmd->cmd_args[1]))
		{
			print_error("cd", cmd->cmd_args[1], strerror(errno));
			return ;
		}
		edit_env_vars(env, buf);
	}
}
