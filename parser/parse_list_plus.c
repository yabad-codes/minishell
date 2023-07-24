/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_plus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:40:11 by yabad             #+#    #+#             */
/*   Updated: 2023/07/24 14:26:24 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

t_redir	*new_redir(t_token_type type, char *file, bool is_quotes)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->hrd_quotes = is_quotes;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir **redir, t_redir *new_redir)
{
	t_redir	*tmp;

	if (*redir)
	{
		tmp = *redir;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
	else
		*redir = new_redir;
}

void	delete_redir(t_redir *redir)
{
	if (redir)
	{
		free(redir->file);
		free(redir);
	}
}

void	clear_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		delete_redir(redir);
	}
}
