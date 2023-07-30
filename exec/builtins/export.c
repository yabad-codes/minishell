/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:45:41 by yabad             #+#    #+#             */
/*   Updated: 2023/07/28 07:44:54 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *cmd, int *pos)
{
	while (cmd[*pos] && cmd[*pos] != '=')
		(*pos)++;
	if (!cmd[*pos])
		return (ft_strdup(cmd));
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

void	print_declare_vars(t_env *env)
{
	while (env)
	{
		printf("declare -x ");
		if (env->key && env->value)
			printf("%s=\"%s\"\n", env->key, env->value);
		if (!env->value)
			printf("%s\n", env->key);
		env = env->next;
	}
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
	if (!cmd->cmd_args[1] || cmd->cmd_args[1][0] == '\0')
		print_declare_vars(*env);
	while (cmd->cmd_args[i])
	{
		pos = 0;
		key = extract_key(cmd->cmd_args[i], &pos);
		if (!is_valid_identifier(key))
		{
			print_error("export", cmd->cmd_args[i], "not a valid identifier");
			free(key);
			i++;
			continue ;
		}
		value = extract_value(cmd->cmd_args[i], &pos);
		modify_key(env, key, value);
		i++;
	}
}
