/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:21:10 by yabad             #+#    #+#             */
/*   Updated: 2023/06/23 15:28:44 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
}	t_node_type;

typedef struct s_redir
{
	t_redir_type	type;
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
t_redir	*new_redir(t_redir_type type, char *file);

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
 * @param type	contain the list of redir (if exist).
 * @return	The newly created node.
*/
t_node	*create_node(t_cmd *cmd, t_node_type type);

/**
 * @brief Delete node
 * @param node	node you want to delete.
*/
void	delete_node(t_node *node);

#endif