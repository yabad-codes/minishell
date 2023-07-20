/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:02:19 by yabad             #+#    #+#             */
/*   Updated: 2023/07/19 16:33:00 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

void	toggle_quote(char c, t_state *toggle)
{
	if (c == '\'' && *toggle == NONE)
		*toggle = SINGLE;
	else if (c == '\"' && *toggle == NONE)
		*toggle = DOUBLE;
	else if ((c == '\'' && *toggle == SINGLE) || \
			(c == '\"' && *toggle == DOUBLE))
		*toggle = NONE;
}

char	*to_str(char c)
{
	char	*s;

	if (c == APPEND || c == HRDOC)
	{
		s = (char *)malloc(3);
		if (c == APPEND)
		{
			s[0] = '>';
			s[1] = '>';
		}
		else
		{
			s[0] = '<';
			s[1] = '<';
		}
		s[2] = '\0';
	}
	else
	{
		s = (char *)malloc(2);
		s[0] = c;
		s[1] = '\0';
	}
	return (s);
}

int	is_delim(char c1, char c2, t_state toggle)
{
	if (toggle != NONE)
		return (FALSE);
	else if (c1 == '>' && c2 == '>')
		return (APPEND);
	else if (c1 == '<' && c2 == '<')
		return (HRDOC);
	else if (c1 == '|')
		return (PIPE);
	else if (c1 == '>')
		return (OUT);
	else if (c1 == '<')
		return (IN);
	else if (c1 == ' ')
		return (c1);
	else
		return (FALSE);
}

int	is_expandable(int prev_delim, char *token)
{
	int	contain_dollar;

	contain_dollar = FALSE;
	while (*token)
	{
		if (*token == '$')
			contain_dollar = TRUE;
		token++;
	}
	return (contain_dollar && (*(token - 1) != '\'') && prev_delim != HRDOC);
}
