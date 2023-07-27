/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:58:22 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/27 17:16:22 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	matched_quotes(t_token *tokens)
{
	t_state	toggle;
	int		i;

	toggle = NONE;
	i = 0;
	while (tokens->token[i])
	{
		toggle_quote(tokens->token[i], &toggle);
		i++;
	}
	return (toggle == NONE);
}

int	is_word_type_before(t_token *prev_token)
{
	if (prev_token == NULL)
		return (FALSE);
	return (prev_token->type == WORD);
}

int	valid_syntax_after(t_token *token)
{
	if (token->next && token->next->type != PIPE)
		return (TRUE);
	return (FALSE);
}

int	is_word_type_after(t_token *token)
{
	if (token->next && token->next->type == WORD)
		return (TRUE);
	return (FALSE);
}
