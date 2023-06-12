/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:46:08 by yabad             #+#    #+#             */
/*   Updated: 2023/06/12 12:01:47 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

typedef enum e_error_code
{
	NO_ERROR,
	UNCLOSED_QUOTE,
	NO_LEFT_COMMAND_BEFORE_PIPE,
	NO_RIGHT_COMMAND_AFTER_PIPE,
	NO_RIGHT_COMMAND_AFTER_REDIRECTION
}	t_error_code;

//1- unclosed quote --> echo "hello --> syntax error: unclosed quotes
//3- no left command before pipe --> | ls --> syntax error near unexpected token `|'
//2- no right command after pipe --> ls | --> syntax error near unexpected token `newline'
//4- no right command after redirection --> ls > --> syntax error near unexpected token `newline'

void	check_syntax_error(t_token *tokens)
{
	int	error_code;

	error_code = get_error_code(tokens);
}
