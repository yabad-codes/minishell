/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:44:15 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:58:14 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_env *env)
{
	while (env)
	{
		if (env->key && env->value)
		{
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
		else
			env = env->next;
	}
}

void	ft_env(t_cmd *cmd, t_env *env)
{
	if (cmd->cmd_args[1])
	{
		printf("env: %s: No such file or directory\n", cmd->cmd_args[1]);
		return ;
	}
	print_env(env);
}
