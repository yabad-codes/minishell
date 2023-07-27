/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:51:29 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 17:19:12 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	t_token	*tokens;
	char	*token;
	t_state	toggle;
	int		delim;
	int		prev_delim;
	bool	is_expandable;
}	t_vars;

typedef struct s_tmp
{
	char	*tmp;
	char	*to_str_tmp;
}	t_tmp;

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
	vars->prev_delim = 0;
	vars->is_expandable = false;
}

void	run_scenarios(t_vars *vars, char c)
{
	t_tmp	tmp;

	if (!vars->delim)
	{
		tmp.tmp = vars->token;
		tmp.to_str_tmp = to_str(c);
		vars->token = ft_strjoin(vars->token, tmp.to_str_tmp);
		free(tmp.tmp);
		free(tmp.to_str_tmp);
		if (vars->toggle != SINGLE && c == '$')
			vars->is_expandable = true;
	}
	else
	{
		if (token_exist(vars->token))
		{
			add_token(&vars->tokens, new_token(vars->token, WORD, \
			is_expandable(vars->is_expandable, vars->prev_delim)));
			vars->token = ft_strdup("");
			vars->is_expandable = false;
		}
		if (vars->delim != ' ')
			add_token(&vars->tokens, new_token(to_str(vars->delim), \
						vars->delim, FALSE));
	}
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
		run_scenarios(&vars, input[i]);
		if (vars.delim == APPEND || vars.delim == HRDOC)
			i++;
		i++;
		if (vars.delim == HRDOC || vars.delim == OUT || vars.delim == IN \
		|| vars.delim == PIPE || vars.delim == APPEND || vars.delim == WORD)
			vars.prev_delim = vars.delim;
	}
	if (token_exist(vars.token))
		add_token(&vars.tokens, new_token(vars.token, WORD, \
			is_expandable(vars.is_expandable, vars.prev_delim)));
	return (vars.tokens);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = get_tokens(input);
	return (tokens);
}
