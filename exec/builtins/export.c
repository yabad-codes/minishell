/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:45:41 by yabad             #+#    #+#             */
/*   Updated: 2023/07/21 16:30:40 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_key(char *cmd, int *pos)
{
	while (cmd[*pos] && cmd[*pos] != '=')
		(*pos)++;
	if (!cmd[*pos])
		return (NULL);
	return (ft_substr(cmd, 0, *pos));
}

char	*extract_value(char *cmd, int *pos)
{
	if (!cmd[*pos])
		return (NULL);
	if (!cmd[*pos + 1])
		return (ft_strdup(""));
	return (ft_substr(cmd, *pos + 1, ft_strlen(cmd) - *pos));
}

void	ft_export(t_cmd *cmd, t_env **env)
{
	char	*key;
	char	*value;
	int		pos;
	int		i;

	i = 1;
	if (!cmd || !cmd->cmd_args || !env)
		return ;
	while (cmd->cmd_args[i])
	{
		if (!is_valid_identifier(cmd->cmd_args[i]))
		{
			print_error("export", \
				cmd->cmd_args[i], "not a valid identifier");
			i++;
			continue ;
		}
		pos = 0;
		key = extract_key(cmd->cmd_args[i], &pos);
		value = extract_value(cmd->cmd_args[i], &pos);
		if (value)
			modify_key(env, key, value);
		i++;
	}
}
