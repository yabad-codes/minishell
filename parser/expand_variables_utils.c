/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:12:41 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/25 17:02:16 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_exit_code(t_token *token_head, char **token_val, \
				char **val)
{
	char	*temp;
	char	*in_toa;

	temp = *val;
	in_toa = ft_itoa(g_data.exit_status);
	*val = ft_strjoin(*val, in_toa);
	free(temp);
	free(in_toa);
	*token_val += 2;
	if (!*val)
		free_tokens_and_exit(token_head);
}
