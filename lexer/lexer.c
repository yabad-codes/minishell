/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:51:29 by yabad             #+#    #+#             */
/*   Updated: 2023/07/19 16:52:09 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

typedef struct s_vars
{
	t_token	*tokens;
	char	*token;
	t_state	toggle;
	int		delim;
	int		prev_delim;
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
	vars->prev_delim = 0;
}

void	run_scenarios(t_vars *vars, char c)
{
	if (!vars->delim)
		vars->token = ft_strjoin(vars->token, to_str(c));
	else
	{
		if (token_exist(vars->token))
		{
			add_token(&vars->tokens, new_token(vars->token, WORD, \
						is_expandable(vars->prev_delim, vars->token)));
			vars->token = ft_strdup("");
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
		if (vars.prev_delim != HRDOC && vars.delim != ' ')
			vars.prev_delim = vars.delim;
		else
			vars.prev_delim = HRDOC;
	}
	if (token_exist(vars.token))
		add_token(&vars.tokens, new_token(vars.token, WORD, \
			is_expandable(vars.prev_delim, vars.token)));
	return (vars.tokens);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	tokens = get_tokens(input);
	return (tokens);
}
