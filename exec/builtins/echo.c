/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:36:29 by yabad             #+#    #+#             */
/*   Updated: 2023/07/20 10:28:49 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		printf("%s", cmd->cmd_args[i]);
		if (cmd->cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (n_option == false)
		printf("\n");
}
