/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:16:11 by yabad             #+#    #+#             */
/*   Updated: 2023/08/01 11:43:47 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		del_key(env, free);
		env = tmp;
	}
}

t_env	*copy_env(char **envp)
{
	t_env	*env;
	char	*instance[2];
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		instance[0] = ft_strchr(envp[i], '=');
		instance[1] = ft_strchr(envp[i], '\0');
		if (!ft_strncmp(envp[i], "OLDPWD", \
			ft_max(ft_strlen("OLDPWD"), instance[0] - envp[i])))
		{
			add_key(&env, new_key(ft_substr(envp[i], 0, \
				instance[0] - envp[i]), NULL));
			i++;
			continue ;
		}
		add_key(&env, new_key(ft_substr(envp[i], 0, instance[0] - envp[i]), \
		ft_substr(envp[i], (instance[0] - envp[i] + 1), \
		instance[1] - instance[0] - 1)));
		i++;
	}
	return (env);
}
