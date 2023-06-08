/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:51:37 by yabad             #+#    #+#             */
/*   Updated: 2023/06/08 12:06:30 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/***********************/
/*   Data structures   */
/***********************/

typedef enum e_token_type {
	APPEND = -3,
	HRDOC = -2,
	WORD = -1,
	PIPE = '|',
	IN = '<',
	OUT = '>'
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
	t_expand		expand;
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
t_token	*new_token(char *content, t_token_type type, t_expand expand);

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

/**
 * @brief Check if a given set is a delimiter
 * @param c1 first character of the set
 * @param c2 second character of the set
 * @param toggle has the value to check if we are inside quotes.
 * @return TRUE if its a delimiter, FALSE otherwise
*/
int		is_delim(char c1, char c2, t_state toggle);

/**
 * @brief turn a character into string
 * @param c the char to be turned
 * @return the string we want
*/
char	*to_str(char c);

/**
 * @brief check if we are inside or outside quotes
 * @param c current position of the input - str[i]
 * @param toggle this value changes to indicate if we are inside, outside quotes
*/
void	toggle_quote(char c, t_state *toggle);

/**
 * @brief check if a token is expandable or not
 * @param token token we want to check
 * @param state token state, inside quotes or not
 * @return TRUE expandable, otherwise FALSE
*/
int		is_expandable(char *token, t_state state);

#endif
