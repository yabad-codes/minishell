/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:02:21 by yabad             #+#    #+#             */
/*   Updated: 2023/07/04 11:55:22 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include "../Libft/libft.h"
# include "parser.h"
# include "lexer.h"

# define ANSI_COLOR_SKY_BLUE   "\033[1;36m"
# define ANSI_COLOR_RESET      "\x1b[0m"

t_token	*lexer(char *input);
t_ast	*parser(t_token *tokens);

void    free_tokens_and_exit(t_token *token_head);

/*	PRINT PROTOTYPE	*/
void	print_ast(t_ast *ast);
void	print_redir(t_redir *redir);
void	print_cmd(t_cmd *cmd);
void	print_tokens(t_token *tokens);
char	*token_type(t_token_type type);
#endif
