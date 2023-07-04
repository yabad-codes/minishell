/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:21:10 by yabad             #+#    #+#             */
/*   Updated: 2023/07/04 22:26:26 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
}	t_node_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd_args;
	t_redir			*redir;
}	t_cmd;

typedef struct s_node
{
	t_cmd		*cmd;
	t_node_type	type;
}	t_node;

typedef struct s_ast
{
	t_node			*node;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

/**
 * @brief Allocate new redir node data type.
 * @param type		redirection type.
 * @param file		the file to redirect to.
 * @return A newly allocated redir data type
*/
t_redir	*new_redir(t_token_type type, char *file);

/**
 * @brief Add the new allocated redir node to a list
 * @param redir			list of redirections.
 * @param new_redir		the new_redir to add
*/
void	add_redir(t_redir **redir, t_redir *new_redir);

/**
 * @brief Delete one redir node
 * @param redir	the node we want to delete
*/
void	delete_redir(t_redir *redir);

/**
 * @brief Delete the list of redirections.
 * @param redir	the head of the list we want to delete.
*/
void	clear_redir(t_redir *redir);

/**
 * @brief Create a command node
 * @param cmd_args	contain the command and its arguments and options.
 * @param redir		contain the list of redir (if exist).
 * @return	The newly created node command.
*/
t_cmd	*create_cmd(char **cmd_args, t_redir *redir);

/**
 * @brief Delete command
 * @param cmd	command you want to delete.
*/
void	delete_cmd(t_cmd *cmd);

/**
 * @brief Create a node (either pipe node or cmd node)
 * @param cmd	cmd node (NULL if the type is NODE_PIPE)
 * @param type	node type (either NODE_PIPE NODE_CMD).
 * @return	The newly created node.
*/
t_node	*create_node(t_cmd *cmd, t_node_type type);

/**
 * @brief Delete node
 * @param node	node you want to delete.
*/
void	delete_node(t_node *node);

/**
 * @brief Expand shell variable that are expandable
 * @param token_head
 * @param is_expand
 * @param token_value
 * @return The value of the variable if EXPANDABLE, or the variable itself if not.
*/
char	*expand_var(t_token *token_head, t_expand is_expand, char *token_value);

/**
 * @brief remove quotes for t_token variables
 * @param token_head the token to process
 * @param token_value the value of the token to process
 * @return the value without quotes
*/
char	*remove_quotes(t_token *token_head, char *token_value);

/**
 * @brief Parse the command
 * @param token_head	the token to process
 * @param tracker		the index of the token we are processing
 * @return The newly created node.
*/
t_ast	*parse_cmd(t_token *token_head, int *tracker);

/**
 * @brief add a new command argument to the command
 * @param cmd_arg	the command argument to add
 * @param new		the new command argument to add
*/
void	add_cmd_arg(char ***cmd_arg, char *new);
void	print_cmd_arg(char **cmd_arg);

#endif
