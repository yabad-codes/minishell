/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:02:21 by yabad             #+#    #+#             */
/*   Updated: 2023/06/28 19:10:57 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include "lexer.h"
# include "../Libft/libft.h"

# define ANSI_COLOR_SKY_BLUE   "\033[1;36m"
# define ANSI_COLOR_RESET      "\x1b[0m"

t_token	*lexer(char *input);

void    free_tokens_and_exit(t_token *token_head);

#endif
