/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:18:54 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:57:03 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, \
			ft_max(ft_strlen(key), ft_strlen(env->key))))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	modify_key(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, \
			ft_max(ft_strlen(key), ft_strlen(tmp->key))))
		{
			free(key);
			if (value != NULL)
			{
				free(tmp->value);
				tmp->value = value;
			}
			return ;
		}
		tmp = tmp->next;
	}
	new = new_key(key, value);
	if (!new)
		return ;
	new->next = *env;
	*env = new;
}

void	del_key(t_env *env, void (*del)(void *))
{
	if (env && del)
	{
		del(env->key);
		del(env->value);
		free(env);
	}
}

void	add_key(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env)
	{
		tmp = *env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
}

t_env	*new_key(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}
