/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:51:29 by yabad             #+#    #+#             */
/*   Updated: 2023/06/07 16:47:06 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	s = (char *)malloc(2);
	if (!s)
		return (NULL);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

int	is_delim(char c1, char c2, t_state toggle)
{
	if (toggle == NONE)
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

t_token	*get_tokens(char *input)
{
	t_token	*tokens;
	t_state	toggle;
	char	*token;
	int		i;

	i = 0;
	toggle = NONE;
	token = "";
	while (input[i])
	{
		toggle_quote(input[i], &toggle);
		if (!delim(input[i]) || (delim(input[i]) && toggle))
			ft_strjoin(token, to_str(input[i]));
		else if (delim(input[i]) == ' ')
			add_token(&tokens, new_token(token, WORD, FALSE));
		else
		{
			add_token(&token, new_token(token, WORD, FALSE));
		}
		i++;
	}
	return (tokens);
}

void	lexer(char *input)
{
	t_token	*tokens;

	tokens = get_tokens(ft_strtrim(input, " "));
	free(input);
	print_tokens(tokens);
	return ;
}
