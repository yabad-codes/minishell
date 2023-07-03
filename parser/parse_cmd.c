/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:09:52 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/03 10:01:26 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	parse_cmd_redir(t_token *token_head, \
						t_redir **redir_list, char *filename)
{
	t_redir	*new;

	if (!filename)
	{
		// free tokens
		exit(1);
	}
	new = new_redir(OUT, filename);
	if (!new)
	{
		// free tokens
		exit(1);
	}
	add_redir(redir_list, new);
}

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
	if (*tracker && token->next && token->next->next)
	{
		token = token->next->next;
		*tracker += 2;
	}
	return (token);
}

void	extract_cmd(t_token *token, t_redir **redir_list, \
						char *cmd_arg, int *tracker)
{
	while (token && token->type != PIPE)
	{
		if (token->type == IN || token->type == OUT || token->type == APPEND)
		{
			add_redir(redir_list, new_redir(token->type, token->next->token));
			token = token->next;
			(*tracker)++;
			if (!token->next)
				break ;
		}
		else if (token->type == WORD)
			cmd_arg = ft_strjoin(ft_strjoin(cmd_arg, token->token), " ");
		else
			//handle HEREDOC
			printf("HEREDOC\n");
		token = token->next;
		(*tracker)++;
	}
}

t_ast	*build_cmd(char *cmd_arg, t_redir *redir_list)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->node = create_node(create_cmd(ft_split(cmd_arg, ' '), redir_list), NODE_CMD);
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
					token_head->token), token_head->type, FALSE));
		token_head = token_head->next;
	}
	clear_tokens(token_head);
	return (new);
}

t_ast	*parse_cmd(t_token *token_head, int *tracker)
{
	t_token	*token;
	t_redir	*redir_list;
	char	*cmd_arg;

	redir_list = NULL;
	cmd_arg = ft_strdup("");
	token_head = expand(token_head);
	token = traverse_to_right_pos(token_head, tracker);
	extract_cmd(token, &redir_list, cmd_arg, tracker);
	return (build_cmd(cmd_arg, redir_list));
}
