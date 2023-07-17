/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:47:55 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/17 16:01:41 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_redir(char *filename, t_redir_error *error, int *fd_out)
{
	if (open(filename, O_EXCL) == -1 && !access(filename, W_OK))
		unlink(filename);
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

void	write_to_tmpfile(char *delim, int *fd_in)
{
	char	*line;
	char	*tmp_line;

	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		tmp_line = ft_strdup(line);
		tmp_line[ft_strlen(tmp_line) - 1] = 0;
		if (!ft_strncmp(tmp_line, delim, ft_strlen(line)))
		{
			free(tmp_line);
			free(line);
			break ;
		}
		free(tmp_line);
		line = expand_var(NULL, TRUE, line);
		write(*fd_in, line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
	}
}

void	herdoc_redir(char *delimiter, t_redir_error *error, int *fd_in)
{
	unlink("/tmp/tmpfile");
	*fd_in = open("/tmp/tmpfile", O_CREAT | O_RDWR, 0644);
	if (*fd_in == -1)
	{
		printf("Error opening the tmpfile\n");
		error->is_error = true;
	}
	write_to_tmpfile(delimiter, fd_in);
	close(*fd_in);
	*fd_in = open("/tmp/tmpfile", O_CREAT | O_RDWR, 0644);
	if (*fd_in == -1)
	{
		printf("Error opening the tmpfile\n");
		error->is_error = true;
		exit(1);
	}
}
