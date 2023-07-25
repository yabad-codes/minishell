/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:46:08 by yabad             #+#    #+#             */
/*   Updated: 2023/07/25 13:20:38 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

typedef enum e_error_code
{
	NO_ERROR,
	UNCLOSED_QUOTES,
	NO_LEFT_CMD_BEFORE_PIPE,
	NO_RIGHT_CMD_AFTER_PIPE,
	NO_RIGHT_FILE_AFTER_REDIRECTION
}	t_error_code;

typedef enum e_separator
{
	NO_SEP,
	QUOTE_SEP,
	PIPE_SEP,
	REDIR_SEP
}	t_separator;

static t_separator	detect_sep(t_token	*token)
{
	if (ft_strchr(token->token, '"') || ft_strchr(token->token, '\''))
		return (QUOTE_SEP);
	else if (!ft_strncmp(token->token, "|", 1))
		return (PIPE_SEP);
	else if (!ft_strncmp(token->token, ">>", ft_strlen(token->token)) || \
		!ft_strncmp(token->token, "<<", ft_strlen(token->token)) || \
		!ft_strncmp(token->token, ">", ft_strlen(token->token)) || \
		!ft_strncmp(token->token, "<", ft_strlen(token->token)))
		return (REDIR_SEP);
	else
		return (NO_SEP);
}

static void	error_message(t_error_code error)
{
	if (error == NO_ERROR)
		return ;
	if (error == UNCLOSED_QUOTES)
		error_file_message(NULL, "syntax error: unclosed quotes");
	else if (error == NO_LEFT_CMD_BEFORE_PIPE)
		error_file_message(NULL, "syntax error near unexpected token");
	else
		error_file_message(NULL, "syntax error near unexpected token");
	g_data.exit_status = 258;
}

static t_error_code	get_error_code(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (detect_sep(tokens) == QUOTE_SEP && !matched_quotes(tokens))
			return (UNCLOSED_QUOTES);
		else if (detect_sep(tokens) == PIPE_SEP && !is_word_type_before(prev))
			return (NO_LEFT_CMD_BEFORE_PIPE);
		else if (detect_sep(tokens) == PIPE_SEP && !valid_syntax_after(tokens))
			return (NO_RIGHT_CMD_AFTER_PIPE);
		else if (detect_sep(tokens) == REDIR_SEP && !is_word_type_after(tokens))
			return (NO_RIGHT_FILE_AFTER_REDIRECTION);
		prev = tokens;
		tokens = tokens->next;
	}
	return (NO_ERROR);
}

int	check_syntax_error(t_token *tokens)
{
	t_error_code	error_code;

	error_code = get_error_code(tokens);
	error_message(error_code);
	return (error_code == NO_ERROR);
}
