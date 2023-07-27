/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:16:11 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:57:19 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env(char **envp)
{
	t_env	*env;
	char	**instance;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		instance = ft_split(envp[i], '=');
		add_key(&env, new_key(instance[0], instance[1]));
		free(instance);
		i++;
	}
	return (env);
}
