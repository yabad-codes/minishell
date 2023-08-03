/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:36:29 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:58:17 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_option(char *cmd_arg)
{
	int	i;

	i = 0;
	if (!cmd_arg)
		return (false);
	if (cmd_arg[i] != '-')
		return (false);
	if (!cmd_arg[i + 1])
		return (false);
	i++;
	while (cmd_arg[i])
	{
		if (cmd_arg[i++] != 'n')
			return (false);
	}
	return (true);
}

void	get_print_pos(t_cmd *cmd, int *i, bool *n_option)
{
	*n_option = is_valid_option(cmd->cmd_args[*i]);
	if (!(*n_option))
		return ;
	(*i)++;
	while (is_valid_option(cmd->cmd_args[*i]))
		(*i)++;
}

void	ft_echo(t_cmd *cmd)
{
	bool	n_option;
	int		i;

	n_option = false;
	i = 1;
	get_print_pos(cmd, &i, &n_option);
	while (cmd->cmd_args[i])
	{
		ft_putstr_fd(cmd->cmd_args[i], 1);
		if (cmd->cmd_args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_option == false)
		ft_putstr_fd("\n", 1);
	g_data.exit_status = 0;
}
