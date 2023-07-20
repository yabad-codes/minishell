/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:56:43 by yabad             #+#    #+#             */
/*   Updated: 2023/07/20 13:18:24 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_cmd *cmd, t_env **env)
{
	int				id;
	t_builtin_type	builtin;
	t_redir_error	is_redir_error;

	handling_redirections(cmd->redir, &is_redir_error);
	builtin = is_builtin(cmd->cmd_args[0]);
	if (builtin)
	{
		execute_builtin(cmd, builtin, env);
		return ;
	}
	id = fork();
	if (id == 0)
	{
		if (cmd->cmd_args && is_redir_error.is_error == false)
		{
			execv(get_path(cmd->cmd_args[0]), cmd->cmd_args);
			if (!ft_strncmp(strerror(errno), "Bad address", 11))
				error_file_message(cmd->cmd_args[0], "command not found");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (id > 0)
		waitpid(id, 0, 0);
	else
		exit(EXIT_FAILURE);
}

void	execute_left(t_ast *ast, t_ast *head, int *fd, t_env **env)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute(ast->left, head, env);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	execute_right(t_ast *ast, t_ast *head, int *fd, t_env **env)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execute(ast->right, head, env);
	close(fd[0]);
	exit(EXIT_SUCCESS);
}

void	close_fds_and_wait_for_childs(int *fd, \
		pid_t lchild_pid, pid_t rchild_pid)
{
	close(fd[1]);
	close(fd[0]);
	waitpid(lchild_pid, 0, 0);
	waitpid(rchild_pid, 0, 0);
}

void	execute(t_ast *ast, t_ast *head, t_env **env)
{
	int		fd[2];
	pid_t	lchild_pid;
	pid_t	rchild_pid;

	if (ast == NULL)
		return ;
	else if (ast->node->type == NODE_CMD)
		execute_cmd(ast->node->cmd, env);
	else if (ast->node->type == NODE_PIPE)
	{
		if (pipe(fd) == -1)
			free_ast_and_exit(head);
		lchild_pid = fork();
		if (lchild_pid == -1)
			free_ast_and_exit(head);
		if (lchild_pid == 0)
			execute_left(ast, head, fd, env);
		rchild_pid = fork();
		if (rchild_pid == -1)
			free_ast_and_exit(head);
		if (rchild_pid == 0)
			execute_right(ast, head, fd, env);
		close_fds_and_wait_for_childs(fd, lchild_pid, rchild_pid);
	}
}
