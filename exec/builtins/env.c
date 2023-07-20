/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:44:15 by yabad             #+#    #+#             */
/*   Updated: 2023/07/16 10:51:35 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
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
