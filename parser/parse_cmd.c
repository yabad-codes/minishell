/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:09:52 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/04 22:40:57 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_token	*traverse_to_right_pos(t_token *token_head, int *tracker)
{
	t_token	*token;
	int		index;

	index = *tracker;
	token = token_head;
	while (token && index)
	{
		token = token->next;
		index--;
	}
	if (*tracker)
	{
		token = token->next;
		(*tracker)++;
	}
	return (token);
}

void	extract_cmd(t_token *token, t_redir **redir_list, \
						char ***cmd_arg, int *tracker)
{
	while (token && token->type != PIPE)
	{
		if (token->type == IN || token->type == OUT || \
			token->type == APPEND || token->type == HRDOC)
		{
			add_redir(redir_list, new_redir(token->type, token->next->token));
			token = token->next;
			(*tracker)++;
			if (!token->next)
				break ;
		}
		else
			add_cmd_arg(cmd_arg, token->token);
		token = token->next;
		(*tracker)++;
	}
}

t_ast	*build_cmd(char **cmd_arg, t_redir *redir_list)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->node = create_node(create_cmd(cmd_arg, redir_list), NODE_CMD);
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

t_token	*expand(t_token *token_head)
{
	t_token	*new;

	new = NULL;
	while (token_head)
	{
		add_token(&new, new_token(expand_var(token_head, token_head->expand, \
				remove_quotes(token_head, token_head->token)), token_head->type, FALSE));
		token_head = token_head->next;
	}
	clear_tokens(token_head);
	return (new);
}

t_ast	*parse_cmd(t_token *token_head, int *tracker)
{
	t_token	*token;
	t_redir	*redir_list;
	char	**cmd_arg;

	redir_list = NULL;
	cmd_arg = NULL;
	token_head = expand(token_head);
	token = traverse_to_right_pos(token_head, tracker);
	extract_cmd(token, &redir_list, &cmd_arg, tracker);
	return (build_cmd(cmd_arg, redir_list));
}
