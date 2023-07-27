/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:11 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 19:07:15 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd_child(t_cmd *cmd, t_env **env)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, child_handler);
	execve(get_path(cmd->cmd_args[0], *env), \
		cmd->cmd_args, cnv_to_envp(*env));
	exec_error(strerror(errno), cmd);
}

int	len_envp(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		if (env->value)
			len++;
		env = env->next;
	}
	return (len);
}

char	**cnv_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*tmp;

	tmp = env;
	envp = malloc(sizeof(char *) * (len_envp(env) + 1));
	if (!envp)
		exit(EXIT_FAILURE);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			envp[i] = ft_strjoin(env->key, "=");
			if (!envp[i])
				exit(EXIT_FAILURE);
			envp[i] = ft_strjoin(envp[i], env->value);
			if (!envp[i])
				exit(EXIT_FAILURE);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
