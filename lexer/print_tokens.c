/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:11:41 by yabad             #+#    #+#             */
/*   Updated: 2023/06/09 11:55:33 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// FILE HAS TO BE REMOVED

#include "../includes/lexer.h"

char	*token_type(t_token_type type)
{
	if (type == APPEND)
		return ("APPEND");
	else if (type == HRDOC)
		return ("HRDOC");
	else if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == IN)
		return ("REDIR_IN");
	else if (type == OUT)
		return ("REDIR_OUT");	
}

void	print_tokens(t_token *tokens)
{
	printf("| %-30s | %-30s | %-30s |\n", "Value", "Type", "Expandable");
	printf("|--------------------------------|--------------------------------|--------------------------------|\n");
	while (tokens)
	{
		printf("| %-30s ", tokens->token);
		printf("| %-30s ", token_type(tokens->type));

		if(tokens->expand == TRUE)
			printf("| %-30s |", "TRUE");
		else
			printf("| %-30s |", "FALSE");
		printf("\n");
		tokens = tokens->next;
	}
}
