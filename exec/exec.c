/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:56:43 by yabad             #+#    #+#             */
/*   Updated: 2023/07/12 19:03:07 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_cmd *cmd)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		execv("/bin/cat", cmd->cmd_args);
		perror("execv failed\n");
		exit(1);
	}
	waitpid(id, 0, 0);
}

void	execute_left(t_ast *ast, t_ast *head, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	execute(ast->left, head);
	close(fd[1]);
	exit(1);
}

void	execute_right(t_ast *ast, t_ast *head, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execute(ast->right, head);
	close(fd[0]);
	exit(1);
}

void	execute(t_ast *ast, t_ast *head)
{
	int	fd[2];
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
		waitpid(lchild_pid, 0, 0);
		waitpid(rchild_pid, 0, 0);
	}
}