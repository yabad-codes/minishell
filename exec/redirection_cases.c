/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:47:55 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/27 17:27:32 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_redir(char *filename, t_redir_error *error, int *fd_out)
{
	if (*fd_out != -1)
		close(*fd_out);
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
	if (*fd_out != -1)
		close(*fd_out);
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
	if (*fd_in != -1)
		close(*fd_in);
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

void	herdoc_redir(int read_end, \
t_redir_error *error, int *fd_in)
{
	if (*fd_in != -1)
		close(*fd_in);
	if (error->is_error == false)
		*fd_in = read_end;
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
		herdoc_redir(list->fd[0], error, &(fds->fd_in));
}
