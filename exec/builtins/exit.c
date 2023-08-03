/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:44:54 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:58:10 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_args_num(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd_args[i])
		i++;
	return (i - 1);
}

void	ft_exit(t_cmd *cmd)
{
	ft_putstr_fd("exit\n", 2);
	if (cmd->cmd_args[1] && !is_digit(cmd->cmd_args[1]))
	{
		print_error("exit", cmd->cmd_args[1], "numeric argument required");
		exit(255);
	}
	if (get_args_num(cmd) > 1)
	{
		error_file_message("exit", "too many arguments");
		return ;
	}
	if (!get_args_num(cmd))
		exit(g_data.exit_status);
	else
		exit(ft_atoi(cmd->cmd_args[1]));
}
