/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:36:29 by yabad             #+#    #+#             */
/*   Updated: 2023/07/17 10:40:22 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	bool	n_option;
	int		i;

	n_option = false;
	i = 1;
	if (cmd->cmd_args[i])
	{
		if (!ft_strncmp(cmd->cmd_args[i], "-n", sizeof(cmd->cmd_args[i])))
		{
			n_option = true;
			i++;
		}
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
}

void	ft_cd(t_cmd *cmd)
{
	printf("execute cd\n");
}

void	ft_pwd(t_cmd *cmd)
{
	printf("execute pwd\n");
}

void	ft_export(t_cmd *cmd)
{
	printf("execute export\n");
}

void	ft_unset(t_cmd *cmd)
{
	printf("execute unset\n");
}
