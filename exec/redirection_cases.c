/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:47:55 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/19 09:35:15 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	out_redir(char *filename, t_redir_error *error, int *fd_out)
{
	if (error->is_error == false)
	{
		*fd_out = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (*fd_out == -1)
		{
			error->filename = filename;
			error->error_message = strerror(errno);
			error->is_error = true;
			return ;
		}
	}
}

void	append_redir(char *filename, t_redir_error *error, int *fd_out)
{
	if (error->is_error == false)
	{
		*fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (*fd_out == -1)
		{
			error->filename = filename;
			error->error_message = strerror(errno);
			error->is_error = true;
			return ;
		}
	}
}

void	in_redir(char *filename, t_redir_error *error, int *fd_in)
{
	if (error->is_error == false)
	{
		*fd_in = open(filename, O_RDONLY, 0644);
		if (*fd_in == -1)
		{
			error->filename = filename;
			error->error_message = strerror(errno);
			error->is_error = true;
			return ;
		}
	}
}

void	herdoc_redir(char *file, \
t_redir_error *error, int *fd_in)
{
	*fd_in = open(file, O_CREAT | O_RDWR, 0644);
	if (*fd_in == -1)
	{
		printf("Error opening the tmpfile\n");
		error->is_error = true;
	}
}

void	launch_redirections(t_redir *list, t_redir_error *error, t_fds *fds)
{
	if (list->type == OUT)
		out_redir(list->file, error, &(fds->fd_out));
	else if (list->type == IN)
		in_redir(list->file, error, &(fds->fd_in));
	else if (list->type == APPEND)
		append_redir(list->file, error, &(fds->fd_out));
	else
		herdoc_redir(list->herdoc_file, error, &(fds->fd_in));
}
