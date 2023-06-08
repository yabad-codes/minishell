/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:51:29 by yabad             #+#    #+#             */
/*   Updated: 2023/06/08 18:54:04 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

typedef struct s_vars
{
	t_token	*tokens;
	char	*token;
	t_state	toggle;
	int		delim;
}	t_vars;

int	token_exist(char *token)
{
	return (token[0] != '\0');
}

void	vars_init(t_vars *vars, int *i)
{
	*i = 0;
	vars->toggle = NONE;
	vars->tokens = NULL;
	vars->token = ft_strdup("");
}

int	run_scenarios(t_vars *vars, int *i, char c)
{
	if (!vars->delim)
			vars->token = ft_strjoin(vars->token, to_str(c));
	else
	{
		if (vars->delim == ' ' && token_exist(vars->token))
			add_token(&vars->tokens, new_token(vars->token, WORD, \
				is_expandable(vars->token, vars->toggle)));
		else if (vars->delim == ' ' && !token_exist(vars->token) && (*i)++)
			return (FALSE);
		else if (vars->delim && vars->delim != ' ')
		{
			if (token_exist(vars->token))
				add_token(&vars->tokens, new_token(vars->token, WORD, \
						is_expandable(vars->token, vars->toggle)));
			add_token(&vars->tokens, new_token(to_str(vars->delim), \
					vars->delim, FALSE));
			if (vars->delim == HRDOC || vars->delim == APPEND)
				(*i)++;
		}
		vars->token = ft_strdup("");
	}
	return (TRUE);
}

t_token	*get_tokens(char *input)
{
	t_vars	vars;
	int		i;

	vars_init(&vars, &i);
	while (input[i])
	{
		toggle_quote(input[i], &(vars.toggle));
		vars.delim = is_delim(input[i], input[i + 1], vars.toggle);
		if (!run_scenarios(&vars, &i, input[i]))
			continue ;
		i++;
	}
	if (token_exist(vars.token))
		add_token(&vars.tokens, new_token(vars.token, WORD, \
			is_expandable(vars.token, vars.toggle)));
	return (vars.tokens);
}

void	lexer(char *input)
{
	t_token	*tokens;

	tokens = get_tokens(input);
	print_tokens(tokens);
	return ;
}
