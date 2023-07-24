/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:12:41 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/24 17:36:05 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_exit_code(t_token *token_head, char *token_val, \
				char **val, int *tok_valpos)
{
	char	*temp;
	char	*in_toa;

	temp = *val;
	if (*token_val == '$' && *(token_val + 1) == '?')
	{
		in_toa = ft_itoa(g_exit_status);
		*val = ft_strjoin(*val, in_toa);
		free(temp);
		free(in_toa);
		*tok_valpos += 2;
		if (!*val)
			free_tokens_and_exit(token_head);
		return (TRUE);
	}
	return (FALSE);
}
