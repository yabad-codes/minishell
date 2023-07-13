/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:51:23 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/13 12:29:21 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	successive_dollars(t_token *token_head, char *token_val, char **val)
{
	char	*temp_val;

	if (*token_val == '$' && *(token_val + 1) == '$')
	{
		temp_val = *val;
		*val = ft_strjoin(temp_val, "$$");
		if (!*val)
			free_tokens_and_exit(token_head);
		free(temp_val);
		return (TRUE);
	}
	return (FALSE);
}

static char	*get_env_val(t_token *token_head, char *str)
{
	char	*locate_env;
	char	*env;
	int		env_len;

	env_len = 0;
	while ((str[env_len] >= 'A' && str[env_len] <= 'Z') \
	|| (str[env_len] >= 'a' && str[env_len] <= 'z'))
		env_len++;
	locate_env = ft_substr(str, 0, env_len);
	if (!locate_env)
		free_tokens_and_exit(token_head);
	env = getenv(locate_env);
	return (free(locate_env), env);
}

static int	detect_env_and_join(t_token *token_head, char *token_val, \
						char **val, int *token_pos)
{
	char	*env;
	char	*temp;

	if (*token_val == '$' && \
		*(token_val + 1) != ' ' && *(token_val + 1) != '\0')
	{
		env = get_env_val(token_head, token_val + 1);
		temp = *val;
		token_val++;
		while ((*token_val >= 'A' && *token_val <= 'Z') \
		|| (*token_val >= 'a' && *token_val <= 'z'))
		{
			(*token_pos)++;
			token_val++;
		}
		(*token_pos)++;
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

static int	join_chars(t_token *token_head, char **val, char c)
{
	if (c)
	{
		*val = ft_charjoin(*val, c);
		if (!*val)
			free_tokens_and_exit(token_head);
		return (TRUE);
	}
	return (FALSE);
}

char	*expand_var(t_token *token_head, t_expand is_expand, char *token_val)
{
	char	*expand_val;
	int		tok_pos;

	if (is_expand == FALSE)
		return (token_val);
	expand_val = ft_strdup("");
	if (!expand_val)
		free_tokens_and_exit(token_head);
	tok_pos = 0;
	while (token_val[tok_pos])
	{
		while (successive_dollars(token_head, &token_val[tok_pos], &expand_val))
			tok_pos += 2;
		if (detect_env_and_join(token_head, &token_val[tok_pos], \
		&expand_val, &tok_pos))
			continue ;
		if (join_chars(token_head, &expand_val, token_val[tok_pos]))
			tok_pos++;
	}
	free(token_val);
	return (expand_val);
}
