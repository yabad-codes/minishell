/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:56:43 by yabad             #+#    #+#             */
/*   Updated: 2023/07/24 09:41:44 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_run(t_cmd *cmd, t_env **env, t_redir_error *error)
{
	t_builtin_type	builtin;

	if (cmd->cmd_args && error->is_error == false)
	{
		if (cmd->cmd_args && !ft_strncmp(cmd->cmd_args[0], "exit", \
		ft_strlen(cmd->cmd_args[0])))
			ft_exit(cmd);
		builtin = is_builtin(cmd->cmd_args[0]);
		if (builtin)
		{
			execute_builtin(cmd, builtin, env);
			exit(EXIT_SUCCESS);
		}
		execv(get_path(cmd->cmd_args[0]), cmd->cmd_args);
		if (!ft_strncmp(strerror(errno), "Bad address", 11))
			error_file_message(cmd->cmd_args[0], "command not found");
		exit(127);
	}
	exit(EXIT_SUCCESS);
}

int	execute_cmd(t_cmd *cmd, t_env **env)
{
	int				id;
	int				status;
	t_redir_error	is_redir_error;

	handling_redirections(cmd->redir, &is_redir_error);
	if (cmd->cmd_args && !ft_strncmp(cmd->cmd_args[0], "exit", \
	ft_strlen(cmd->cmd_args[0])))
		ft_exit(cmd);
	id = fork();
	if (id == 0)
		cmd_run(cmd, env, &is_redir_error);
	else if (id > 0)
	{
		waitpid(id, &status, 0);
		if (((*(int *)&(status)) & 0177) == 0)
			return (((*(int *)&(status)) >> 8) & 0x000000ff);
	}
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
	int	status;

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
}

int		execute(t_ast *ast, t_ast *head, t_env **env)
{
	int		fd[2];
	int		status;
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
}
	