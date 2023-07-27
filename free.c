/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:08:42 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/27 17:21:06 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_and_exit(t_token *token_head)
{
	clear_tokens(token_head);
	exit(EXIT_FAILURE);
}

void	free_ast_and_exit(t_ast *ast)
{
	free_ast(ast);
	exit(EXIT_FAILURE);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->node)
		delete_node(ast->node);
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	free(ast);
}
