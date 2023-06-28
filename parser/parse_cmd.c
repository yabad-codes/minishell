/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:09:52 by ael-maar          #+#    #+#             */
/*   Updated: 2023/06/27 18:20:04 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_cmd_redir(t_token *token_head, t_redir **redir_list, char *filename)
{
	t_redir	*new;

	if (!filename)
	{
		// free tokens
		exit(1);
	}
	new = new_redir(REDIR_OUT, filename);
	if (!new)
	{
		// free tokens
		exit(1);
	}
	add_redir(redir_list, new);
}

