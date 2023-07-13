/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:20:54 by yabad             #+#    #+#             */
/*   Updated: 2023/07/04 22:34:05 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_token	*search_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
			return (token);
		token = token->next;
	}
	return (NULL);
}

t_ast	*build_ast(t_token *token_head, t_token *token_pipe, int *tracker_cmd)
{
	t_ast	*ast;

	ast = NULL;
	if (token_pipe)
	{
		ast = malloc(sizeof(t_ast));
		if (!ast)
		{
			// free tokens
			exit(1);
		}
		ast->node = create_node(NULL, NODE_PIPE);
		if (!ast->node)
		{
			// free tokens
			exit(1);
		}
		ast->left = build_ast(token_head, search_pipe(token_pipe->next), tracker_cmd);
		ast->right = parse_cmd(token_head, tracker_cmd);
		return (ast);
	}
	return (parse_cmd(token_head, tracker_cmd));
}

t_ast	*parser(t_token *tokens)
{
	t_ast	*ast;
	int		tracker_cmd;

	ast = NULL;
	tracker_cmd = 0;
	ast = build_ast(tokens, search_pipe(tokens), &tracker_cmd);
	print_ast(ast);
	return (ast);
}
