/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 08:27:45 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/27 17:16:00 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *content, t_token_type type, t_expand expand)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new)
	{
		new->token = content;
		new->type = type;
		new->expand = expand;
		new->next = NULL;
	}
	return (new);
}

void	add_token(t_token **token, t_token *new_token)
{
	t_token	*temp;

	if (token && new_token)
	{
		if (*token)
		{
			temp = *token;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_token;
			return ;
		}
		(*token) = new_token;
	}
}

void	delete_token(t_token *token)
{
	if (token)
	{
		free(token->token);
		free(token);
	}
}

void	clear_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		delete_token(temp);
	}
}

void	clear_tokens_without_values(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}
}
