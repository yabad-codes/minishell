/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:20:54 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 21:00:07 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			free_tokens_and_exit(token_head);
		ast->node = create_node(NULL, NODE_PIPE);
		if (!ast->node)
			free_tokens_and_exit(token_head);
		ast->left = build_ast(token_head, \
				search_pipe(token_pipe->next), tracker_cmd);
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
	tokens = expand(tokens);
	ast = build_ast(tokens, search_pipe(tokens), &tracker_cmd);
	return (ast);
}
