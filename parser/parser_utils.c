/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:21:42 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/27 21:00:03 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_quote_vars
{
	char	*val;
	char	*dst;
	int		in_single_quotes;
	int		in_double_quotes;
}	t_quote_vars;

char	*ft_charjoin(char *str, char c)
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

bool	quotes_checks(char token_c, t_quote_vars *vars, \
			t_token *token, t_token *prev_tok)
{
	if (token_c == '\'' && !vars->in_double_quotes)
	{
		vars->in_single_quotes = !vars->in_single_quotes;
		if (prev_tok != NULL && prev_tok->type == HRDOC)
			token->hrd_quotes = true;
		return (true);
	}
	if (token_c == '\"' && !vars->in_single_quotes)
	{
		vars->in_double_quotes = !vars->in_double_quotes;
		if (prev_tok != NULL && prev_tok->type == HRDOC)
			token->hrd_quotes = true;
		return (true);
	}
	return (false);
}

char	*remove_quotes(t_token *token_head, char *token_value, \
						t_token *token, t_token *prev_tok)
{
	t_quote_vars	vars;

	vars.val = malloc(ft_strlen(token_value) + 1);
	if (!vars.val)
		free_tokens_and_exit(token_head);
	vars.dst = vars.val;
	vars.in_single_quotes = 0;
	vars.in_double_quotes = 0;
	token->hrd_quotes = false;
	while (*token_value)
	{
		if (quotes_checks(*token_value, &vars, token, prev_tok))
		{
			token_value++;
			continue ;
		}
		*vars.dst++ = *token_value++;
	}
	*vars.dst = '\0';
	return (vars.val);
}
