/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:11:41 by yabad             #+#    #+#             */
/*   Updated: 2023/06/08 19:33:37 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// FILE HAS TO BE REMOVED

#include "../includes/lexer.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("token : %s\n", tokens->token);
		tokens = tokens->next;
	}
}
