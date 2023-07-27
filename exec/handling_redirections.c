/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:13:03 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/27 19:12:50 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_proc
{
	CHILD,
	PARENT
}	t_proc;

void	write_to_pipe(bool hrd_quotes, char *delim, int fd_out)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	while (line != NULL)
	{
		if (!ft_strncmp(line, delim, ft_max(ft_strlen(line), ft_strlen(delim))))
		{
			free(line);
			break ;
		}
		if (hrd_quotes == false)
			line = expand_var(NULL, TRUE, line);
		tmp = ft_strjoin(line, "\n");
		if (!tmp)
			exit(EXIT_FAILURE);
		free(line);
		line = tmp;
		write(fd_out, line, ft_strlen(line));
		free(line);
		line = readline("> ");
	}
}

void	child_writing_in_pipe(t_redir *redir, t_proc proc, int id)
{
	int	status;

	if (proc == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		close(redir->fd[0]);
		write_to_pipe(redir->hrd_quotes, redir->file, redir->fd[1]);
		close(redir->fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(id, &status, 0);
		close(redir->fd[1]);
		if (((*(int *)&(status)) & 0177) != 0177 \
			&& ((*(int *)&(status)) & 0177) != 0)
		{
			g_data.exit_status = 1;
			g_data.atomic = true;
		}
	}
}

void	open_pipe_and_write(t_redir *redir)
{
	int	id;

	while (redir && g_data.atomic == false)
	{
		if (redir->type == HRDOC)
		{
			pipe(redir->fd);
			id = fork();
			if (id == 0)
				child_writing_in_pipe(redir, CHILD, 0);
			else if (id > 0)
				child_writing_in_pipe(redir, PARENT, id);
			else
				exit(EXIT_FAILURE);
		}
		redir = redir->next;
	}
}

void	handling_herdocs(t_ast *ast, int *num)
{
	t_redir	*redir;

	if (ast->node->type == NODE_CMD)
	{
		redir = ast->node->cmd->redir;
		open_pipe_and_write(redir);
	}
	if (ast->node->type == NODE_PIPE)
	{
		handling_herdocs(ast->left, num);
		handling_herdocs(ast->right, num);
	}
}

void	handling_redirections(t_redir *list, t_redir_error *error)
{
	t_fds			fds;

	fds.fd_in = -1;
	fds.fd_out = -1;
	error->is_error = false;
	while (list)
	{
		launch_redirections(list, error, &fds);
		list = list->next;
	}
	if (error->is_error == false)
	{
		if (fds.fd_in != -1)
		{
			dup2(fds.fd_in, STDIN_FILENO);
			close(fds.fd_in);
		}
		if (fds.fd_out != -1)
		{
			dup2(fds.fd_out, STDOUT_FILENO);
			close(fds.fd_out);
		}
		return ;
	}
	error_file_message(error->filename, error->error_message);
}
