/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:21:10 by yabad             #+#    #+#             */
/*   Updated: 2023/06/15 13:22:28 by yabad            ###   ########.fr       */
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

#endif