/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:02:48 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:59:59 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(char **cmd_args, t_redir *redir)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_args = cmd_args;
	cmd->redir = redir;
	return (cmd);
}

void	clear_cmd_args(char **cmd_arg)
{
	int	i;

	if (!cmd_arg)
		return ;
	i = -1;
	while (cmd_arg[++i])
		free(cmd_arg[i]);
	free(cmd_arg);
}

void	delete_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->cmd_args)
			clear_cmd_args(cmd->cmd_args);
		if (cmd->redir)
			clear_redir(cmd->redir);
		free(cmd);
	}
}

t_node	*create_node(t_cmd *cmd, t_node_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->type = type;
	return (node);
}

void	delete_node(t_node *node)
{
	if (!node)
		return ;
	if (node->cmd)
		delete_cmd(node->cmd);
	free(node);
}
