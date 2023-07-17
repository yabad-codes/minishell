/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:56:43 by yabad             #+#    #+#             */
/*   Updated: 2023/07/17 13:19:35 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* This is Anouar updated version */
void	execute_cmd(t_cmd *cmd)
{
	int				id;
	t_builtin_type	builtin;
	t_redir_error	is_redir_error;

	id = fork();
	if (id == 0)
	{
		handling_redirections(cmd->redir, &is_redir_error);
		if (cmd->cmd_args && is_redir_error.is_error == false)
		{
			builtin = is_builtin(cmd->cmd_args[0]);
			if (builtin)
			{
				execute_builtin(cmd, builtin);
				exit(EXIT_SUCCESS) ;
			}
			execv(get_path(cmd->cmd_args[0]), cmd->cmd_args);
			if (!ft_strncmp(strerror(errno), "Bad address", 11))
				error_file_message(cmd->cmd_args[0], "command not found");
			exit(EXIT_FAILURE);
		}
	}
	else if (id > 0)
		waitpid(id, 0, 0);
	else
		exit(EXIT_FAILURE);
}

/* This is Yahya version */
// void	execute_cmd(t_cmd *cmd)
// {
// 	int				id;
// 	t_builtin_type	builtin;

// 	builtin = is_builtin(cmd->cmd_args[0]);
// 	if (builtin)
// 	{
// 		execute_builtin(cmd, builtin);
// 		return ;
// 	}
// 	id = fork();
// 	if (id == 0)
// 	{
// 		execv(get_path(cmd->cmd_args[0]), cmd->cmd_args);
// 		perror("execv failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 		waitpid(id, 0, 0);
// }

void	execute_left(t_ast *ast, t_ast *head, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute(ast->left, head);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	execute_right(t_ast *ast, t_ast *head, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execute(ast->right, head);
	close(fd[0]);
	exit(EXIT_SUCCESS);
}

void	execute(t_ast *ast, t_ast *head)
{
	int		fd[2];
	pid_t	lchild_pid;
	pid_t	rchild_pid;

	if (ast == NULL)
		return ;
	else if (ast->node->type == NODE_CMD)
		execute_cmd(ast->node->cmd);
	else if (ast->node->type == NODE_PIPE)
	{
		if (pipe(fd) == -1)
			free_ast_and_exit(head);
		lchild_pid = fork();
		if (lchild_pid == -1)
			free_ast_and_exit(head);
		if (lchild_pid == 0)
			execute_left(ast, head, fd);
		rchild_pid = fork();
		if (rchild_pid == 0)
			execute_right(ast, head, fd);
		close(fd[1]);
		close(fd[0]);
		waitpid(lchild_pid, 0, 0);
		waitpid(rchild_pid, 0, 0);
	}
}
