/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:46:25 by yabad             #+#    #+#             */
/*   Updated: 2023/07/21 10:09:44 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_elem(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(current->key, key, \
			ft_max(ft_strlen(current->key), ft_strlen(key))))
		{
			if (!prev)
				*env = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (!cmd || !cmd->cmd_args || !env)
		return ;
	while (cmd->cmd_args[i])
	{
		remove_env_elem(env, cmd->cmd_args[i]);
		i++;
	}
}
