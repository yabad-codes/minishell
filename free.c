/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:08:42 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/11 19:46:21 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/lexer.h"
#include "includes/parser.h"

void    free_ast_and_exit(t_ast *ast)
{
    (void)ast;
    printf("free_ast_and_exit\n");
    exit(1);
}

void    free_tokens_and_exit(t_token *token_head)
{
    (void)token_head;
    printf("free_tokens_and_exit\n");
    exit(1);
    // implementation of this function
}
