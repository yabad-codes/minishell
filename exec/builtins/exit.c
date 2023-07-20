/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:44:54 by yabad             #+#    #+#             */
/*   Updated: 2023/07/20 11:34:08 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_digit(char *str)
{
	while (*str)
	{
		if (!(*str <= '9' && *str >= '0'))
			return (false);
		str++;
	}
	return (true);
}

static void	print_error(char *arg, char *msg)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("bash: exit: ", 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
}

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
	if (cmd->cmd_args[1] && !is_digit(cmd->cmd_args[1]))
	{
		print_error(cmd->cmd_args[1], "numeric argument required\n");
		exit(255);
	}
	if (get_args_num(cmd) > 1)
	{
		print_error(NULL, "too many arguments\n");
		return ;
	}
	if (get_args_num(cmd) == 0)
		exit(EXIT_SUCCESS);
	else
		exit(ft_atoi(cmd->cmd_args[1]));
}
