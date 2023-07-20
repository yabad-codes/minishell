/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:18:54 by yabad             #+#    #+#             */
/*   Updated: 2023/07/15 18:20:15 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	modify_key(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
		{
			free(env->value);
			env->value = value;
			return ;
		}
		env = env->next;
	}
	add_key(&env, new_key(key, value));
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
