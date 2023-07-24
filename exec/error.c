/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:15:01 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/23 10:58:32 by yabad            ###   ########.fr       */
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
}

void	exec_error(char *msg, t_cmd *cmd)
{
	if (!ft_strncmp(strerror(errno), "Bad address", 11))
	{
		error_file_message(cmd->cmd_args[0], "command not found");
		exit(EXIT_FAILURE);
	}
	error_file_message(cmd->cmd_args[0], msg);
	exit(EXIT_FAILURE);
}
