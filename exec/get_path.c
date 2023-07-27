/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:14:42 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:58:37 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_correct_path(char **path_env, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	path = "";
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		exit(EXIT_FAILURE);
	while (path_env[i])
	{
		path = ft_strjoin(path_env[i], cmd);
		if (!path)
			exit(EXIT_FAILURE);
		if (access(path, X_OK) == 0)
		{
			free(cmd);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_env *env)
{
	char	**path_env;
	char	*correct_path;
	char	*path_var;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	path_var = get_value(env, "PATH");
	if (!path_var)
		return (NULL);
	path_env = ft_split(path_var, ':');
	correct_path = get_correct_path(path_env, cmd);
	return (correct_path);
}
