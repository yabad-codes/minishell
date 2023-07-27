/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:13:03 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/27 10:57:37 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*generate_tmp_file(int *num)
// {
// 	char		*new_tmp_file;
// 	char		*num_cnv;

// 	num_cnv = ft_itoa(*num);
// 	new_tmp_file = ft_strjoin("/tmp/tmpfile", num_cnv);
// 	if (!new_tmp_file || !num_cnv)
// 		exit(EXIT_FAILURE);
// 	free(num_cnv);
// 	(*num)++;
// 	return (new_tmp_file);
// }

// void	write_to_tmpfile(bool is_quotes, char *delim, int fd_in)
// {
// 	char	*line;

// 	line = readline("> ");
// 	while (line != NULL)
// 	{
// 		if (!ft_strncmp(line, delim, ft_max(ft_strlen(line), ft_strlen(delim))))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (is_quotes == false)
// 			line = expand_var(NULL, TRUE, line);
// 		write(fd_in, line, ft_strlen(line));
// 		write(fd_in, "\n", 1);
// 		free(line);
// 		line = readline("> ");
// 	}
// }

//void write_to_pipe(bool hrd_quotes, char *delim, int fd_out)
/*this function will join the lines of the heredoc and write them to the pipe.*/

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

// void	herdoc_handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		// rl_redisplay();
// 		// exit(2);
// 		// signal(SIGINT, SIG_DFL);
// 	}
// }

void	open_pipe_and_write(t_redir *redir)
{
	int	id;
	int	status;

	while (redir && g_data.exit_status != 130 && g_data.exit_status != 131)
	{
		if (redir->type == HRDOC)
		{
			pipe(redir->fd);
			id = fork();
			if (id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				close(redir->fd[0]);
				write_to_pipe(redir->hrd_quotes, redir->file, redir->fd[1]);
				close(redir->fd[1]);
				exit(EXIT_SUCCESS);
			}
			else if (id > 0)
			{
				waitpid(id, &status, 0);
				close(redir->fd[1]);
				if (((*(int *)&(status)) & 0177) != 0177 \
					&& ((*(int *)&(status)) & 0177) != 0)
				{
					// printf("exit status: %d\n", g_data.exit_status);
					g_data.exit_status = 128 + ((*(int *)&(status)) & 0177);
				}
				// printf("exit status: %d\n", g_data.exit_status);
			}
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
