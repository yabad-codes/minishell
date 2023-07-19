/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:13:03 by ael-maar          #+#    #+#             */
/*   Updated: 2023/07/19 09:56:06 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*generate_tmp_file(int *num)
{
	char		*new_tmp_file;
	char		*num_cnv;

	num_cnv = ft_itoa(*num);
	new_tmp_file = ft_strjoin("/tmp/tmpfile", num_cnv);
	if (!new_tmp_file || !num_cnv)
		exit(EXIT_FAILURE);
	free(num_cnv);
	(*num)++;
	return (new_tmp_file);
}

void	write_to_tmpfile(char *delim, int fd_in)
{
	char	*line;

	line = readline("> ");
	while (line != NULL)
	{
		if (!ft_strncmp(line, delim, ft_strlen(line)) && line[0] != '\0' \
		&& line[ft_strlen(line) - 1] == delim[ft_strlen(delim) - 1])
		{
			free(line);
			break ;
		}
		line = expand_var(NULL, TRUE, line);
		write(fd_in, line, ft_strlen(line));
		write(fd_in, "\n", 1);
		line = readline("> ");
	}
}

void	open_tmpfile_and_write(t_redir *redir, int *num)
{
	int	fd;

	while (redir)
	{
		if (redir->type == HRDOC)
		{
			redir->herdoc_file = generate_tmp_file(num);
			unlink(redir->herdoc_file);
			fd = open(redir->herdoc_file, O_CREAT | O_RDWR, 0644);
			if (fd == -1)
				printf("Error opening the tmpfile\n");
			write_to_tmpfile(redir->file, fd);
			close(fd);
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
		open_tmpfile_and_write(redir, num);
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
	exit(EXIT_FAILURE);
}