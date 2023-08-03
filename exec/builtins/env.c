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
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
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
		print_error("env", cmd->cmd_args[1], "No such file or directory");
		g_data.exit_status = 127;
		return ;
	}
	print_env(env);
}
