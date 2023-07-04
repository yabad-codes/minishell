/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:21:42 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/04 11:21:05 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

static char	*ft_charjoin(char *str, char c)
{
	char	*res;
	int		i;

	res = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!res)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i++] = c;
	res[i] = '\0';
	free(str);
	return (res);
}

char	*remove_quotes(t_token *token_head, char *token_value)
{
	char	*val;
	t_state	toggle;

	val = ft_strdup("");
	toggle = NONE;
	if (!val)
		free_tokens_and_exit(token_head);
	while (*token_value)
	{
		if (*token_value == '\'' && toggle == NONE)
			toggle = SINGLE;
		else if (*token_value == '\"' && toggle == NONE)
			toggle = DOUBLE;
		else if ((*token_value == '\'' && toggle == SINGLE) || \
			(*token_value == '\"' && toggle == DOUBLE))
			toggle = NONE;
		else
		{
			val = ft_charjoin(val, *token_value);
			if (!val)
				free_tokens_and_exit(token_head);
		}
		token_value++;
	}
	return (val);
}

char	*get_env_val(t_token *token_head, char *str)
{
	char	*locate_env;
	char	*env;

	locate_env = ft_strchr(str, ' ');
	if (!locate_env)
		ft_strchr(str, '\0');
	locate_env = ft_substr(str, 0, locate_env - str);
	if (!locate_env)
		free_tokens_and_exit(token_head);
	env = getenv(locate_env);
	return (free(locate_env), env);
}

int	detect_env_and_join(t_token *token_head, char *token_value, char **val)
{
	char	*env;
	char	*temp;

	if (*token_value == '$' && \
		*(token_value + 1) != ' ' && *(token_value + 1) != '\0')
	{
		env = get_env_val(token_head, token_value + 1);
		temp = *val;
		if (!env)
			return (TRUE);
		*val = ft_strjoin(*val, env);
		free(temp);
		if (!*val)
			free_tokens_and_exit(token_head);
		return (TRUE);
	}
	return (FALSE);
}

char	*expand_var(t_token *token_head, t_expand is_expand, char *token_value)
{
	char	*val;

	if (is_expand == FALSE)
		return (token_value);
	val = ft_strdup("");
	if (!val)
		free_tokens_and_exit(token_head);
	while (*token_value)
	{
		if (detect_env_and_join(token_head, token_value, &val) == TRUE)
		{
			while (*token_value != ' ' && *token_value != '\0')
				token_value++;
		}
		if (*token_value != '\0')
		{
			val = ft_charjoin(val, *token_value);
			if (!val)
				free_tokens_and_exit(token_head);
			token_value++;
		}
	}
	return (val);
}
