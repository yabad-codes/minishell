/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:51:37 by yabad             #+#    #+#             */
/*   Updated: 2023/06/07 13:27:47 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/***********************/
/*   Data structures   */
/***********************/

typedef enum e_token_type {
	WORD = -1,
	PIPE = '|',
	IN = '<',
	OUT = '>',
	HRDOC,
	APPEND
}	t_token_type;

typedef enum e_state {
	NONE,
	SINGLE,
	DOUBLE
}	t_state;

typedef enum e_expand {
	FALSE,
	TRUE
}	t_expand;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	t_state			expand;
	struct s_token	*next;
}	t_token;


/***********************/
/*      Functions      */
/***********************/

/**
 * @brief Allocate new token node data type.
 * @param content	The token value.
 * @param type		The token type.
 * @param expand	This is for environment variable, getting expanded or not.
 * @return A newly allocated token data type
*/
t_token	*new_token(char *content, t_token_type type, t_state expand);

/**
 * @brief Add a token node at the tail of the list
 * @param token	The token list
 * @param new_token The newly allocated token
*/
void	add_token(t_token **token, t_token *new_token);

/**
 * @brief Delete a token node
 * @param token The token node
*/
void	delete_token(t_token *token);

/**
 * @brief Clear the list of tokens
 * @param tokens The token list
*/
void	clear_tokens(t_token *tokens);

#endif
