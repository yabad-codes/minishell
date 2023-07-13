/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:21:42 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/12 14:52:34 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

char	*ft_charjoin(char *str, char c)
{
	char	*res;
	int		i;

	res = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!res)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i++] = c;
	res[i] = '\0';
	free(str);
	return (res);
}

char	*remove_quotes(t_token *token_head, char *token_value)
{
	char	*val;
	t_state	toggle;

	val = ft_strdup("");
	toggle = NONE;
	if (!val)
		free_tokens_and_exit(token_head);
	while (*token_value)
	{
		if (*token_value == '\'' && toggle == NONE)
			toggle = SINGLE;
		else if (*token_value == '\"' && toggle == NONE)
			toggle = DOUBLE;
		else if ((*token_value == '\'' && toggle == SINGLE) || \
			(*token_value == '\"' && toggle == DOUBLE))
			toggle = NONE;
		else
		{
			val = ft_charjoin(val, *token_value);
			if (!val)
				free_tokens_and_exit(token_head);
		}
		token_value++;
	}
	return (val);
}
