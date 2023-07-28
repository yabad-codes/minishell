/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:13:34 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:58:28 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_exec_vars
{
	int				id;
	int				status;
	t_redir_error	is_redir_error;
	t_builtin_type	builtin;
}	t_exec_vars;

int	execute_cmd(t_cmd *cmd, t_env **env)
{
	t_exec_vars	v;

	handling_redirections(cmd->redir, &(v.is_redir_error));
	if (cmd->cmd_args && v.is_redir_error.is_error == false)
	{
		v.builtin = is_builtin(cmd->cmd_args[0]);
		if (v.builtin)
			return (execute_builtin(cmd, v.builtin, env), 0);
		v.id = fork();
		if (v.id == 0)
			execute_cmd_child(cmd, env);
		else if (v.id > 0)
		{
			waitpid(v.id, &(v.status), 0);
			if (((*(int *)&(v.status)) & 0177) == 0)
				return (((*(int *)&(v.status)) >> 8) & 0x000000ff);
			if (((*(int *)&(v.status)) & 0177) != 0177 \
			&& ((*(int *)&(v.status)) & 0177) != 0)
				return (128 + ((*(int *)&(v.status)) & 0177));
		}
		else
			exit(EXIT_FAILURE);
	}
	return (-1);
}

void	execute_left(t_ast *ast, t_ast *head, int *fd, t_env **env)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute(ast->left, head, env);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	execute_right(t_ast *ast, t_ast *head, int *fd, t_env **env)
{
	int	status;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, child_handler);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	status = execute(ast->right, head, env);
	close(fd[0]);
	exit(status);
}

int	close_fds_and_wait_for_childs(int *fd, \
		pid_t lchild_pid, pid_t rchild_pid)
{
	int	status;

	close(fd[1]);
	close(fd[0]);
	waitpid(lchild_pid, 0, 0);
	waitpid(rchild_pid, &status, 0);
	if (((*(int *)&(status)) & 0177) == 0)
		return (((*(int *)&(status)) >> 8) & 0x000000ff);
	if (((*(int *)&(status)) & 0177) != 0177 \
	&& ((*(int *)&(status)) & 0177) != 0)
		return (((*(int *)&(status)) & 0177));
	return (-1);
}

int	execute(t_ast *ast, t_ast *head, t_env **env)
{
	int		fd[2];
	pid_t	lchild_pid;
	pid_t	rchild_pid;

	if (ast->node->type == NODE_CMD)
		return (execute_cmd(ast->node->cmd, env));
	if (ast->node->type == NODE_PIPE)
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
		return (close_fds_and_wait_for_childs(fd, lchild_pid, rchild_pid));
	}
	return (-1);
}
