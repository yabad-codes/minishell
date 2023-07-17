/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:13:03 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/17 13:19:23 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_fds
{
	int	fd_out;
	int	fd_in;
}	t_fds;

void	launch_redirections(t_redir *list, t_redir_error *error, t_fds *fds)
{
	if (list->type == OUT)
		out_redir(list->file, error, &(fds->fd_out));
	else if (list->type == IN)
		in_redir(list->file, error, &(fds->fd_in));
	else if (list->type == APPEND)
		append_redir(list->file, error, &(fds->fd_out));
	else
		herdoc_redir(list->file, error, &(fds->fd_in));
}

void	handling_redirections(t_redir *list, t_redir_error *error)
{
	t_fds			fds;

	fds.fd_in = 0;
	fds.fd_out = 0;
	error->is_error = false;
	while (list)
	{
		launch_redirections(list, error, &fds);
		list = list->next;
	}
	if (error->is_error == false)
	{
		if (fds.fd_in)
			dup2(fds.fd_in, STDIN_FILENO);
		if (fds.fd_out)
			dup2(fds.fd_out, STDOUT_FILENO);
		return ;
	}
	error_file_message(error->filename, error->error_message);
}
