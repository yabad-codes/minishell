/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:20:54 by yabad             #+#    #+#             */
/*   Updated: 2023/06/26 15:03:30 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
/*
build_ast(token_head, token_pipe, tracker_cmd) --> return t_ast cmd node
e:g echo
parse_cmd(token_head, tracker_cmd)


parser(token_head) --> build_ast(token_head, search_pipe(token_head), tracker_cmd) --> parse_cmd(token_head, tracker_cmd)

    CMD1 | CMD2 | CMD3
              PIPE
       PIPE -------- CMD3
CMD1 --------- CMD2
 ex: > file echo Hi
    echo Hi > file
    echo Hi > file > file1 > file2
parse_cmd():
1- Traverse to the first word token after pipe (using the tracker_cmd var).
2- Traverse the tokens one by one until we reach the pipe or the end of the token list.
3- If you encounter a redir token, then generate a redir node and add it to the redir list.
4- If the word token after the redir token, is expandable then expand it (all with one function).
5- otherwise generate the cmd arguments in the cmd_args variable,
and apply the same steps of 4 of the redir part, if the token is expandable
'$CMD' -l
*/

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
	int		tracker_cmd;

	tracker_cmd = 0;
	return (build_ast(tokens, search_pipe(tokens), &tracker_cmd));
}
