/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:15:01 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/26 13:17:39 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_file_message(char *filename, char *error_message)
{
	ft_putstr_fd("bash: ", 2);
	if (filename)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
	g_data.exit_status = 1;
}

void	print_error(char *cmd, char *filename, char *error_message)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
	g_data.exit_status = 1;
}

void	exec_error(char *msg, t_cmd *cmd)
{
	if (errno == EACCES || errno == EFAULT)
	{
		error_file_message(cmd->cmd_args[0], "command not found");
		exit(127);
	}
	error_file_message(cmd->cmd_args[0], msg);
	exit(127);
}
