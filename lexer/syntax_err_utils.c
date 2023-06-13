/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 08:58:22 by ael-maar          #+#    #+#             */
/*   Updated: 2023/06/13 13:24:28 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	matched_quotes(t_token **tokens)
{
	t_state	toggle;
	int		i;

	toggle = NONE;
	i = 0;
	while ((*tokens)->token[i])
	{
		if ((*tokens)->token[i] == '"' && toggle == NONE)
			toggle = DOUBLE;
		else if ((*tokens)->token[i] == '\'' && toggle == NONE)
			toggle = SINGLE;
		else if (((*tokens)->token[i] == '"' && toggle == DOUBLE) ||\
		((*tokens)->token[i] == '\'' && toggle == SINGLE))
			toggle = NONE;
		i++;
	}
	return (toggle == NONE);
}

int	is_word_type_before(t_token *prev_token)
{
	if(prev_token == NULL)
		return (FALSE);

	return (prev_token->type == WORD);
}

int	is_word_type_after(t_token *token)
{
	if(token == NULL)
		return (FALSE);
	if (token->next)
	{
		if (token->next->type == WORD)
			return (TRUE);	
	}
	return (FALSE);
}
