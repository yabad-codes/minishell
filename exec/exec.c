/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:13:34 by yabad             #+#    #+#             */
/*   Updated: 2023/07/26 20:08:25 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGINT)
		signal(SIGINT, SIG_DFL);
}

char	**cnv_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		exit(EXIT_FAILURE);
	i = 0;
	while (env)
	{
		envp[i] = ft_strjoin(env->key, "=");
		if (!envp[i])
			exit(EXIT_FAILURE);
		envp[i] = ft_strjoin(envp[i], env->value);
		if (!envp[i])
			exit(EXIT_FAILURE);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	execute_cmd(t_cmd *cmd, t_env **env)
{
	int				id;
	int				status;
	t_redir_error	is_redir_error;
	t_builtin_type	builtin;

	handling_redirections(cmd->redir, &is_redir_error);
	if (cmd->cmd_args)
	{
		builtin = is_builtin(cmd->cmd_args[0]);
		if (builtin)
		{
			execute_builtin(cmd, builtin, env);
			return (0);
		}
		id = fork();
		if (id == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, child_handler);
			execve(get_path(cmd->cmd_args[0], *env), cmd->cmd_args, cnv_to_envp(*env));
			exec_error(strerror(errno), cmd);	
		}
		else if (id > 0)
		{
			waitpid(id, &status, 0);
			if (((*(int *)&(status)) & 0177) == 0)
				return (((*(int *)&(status)) >> 8) & 0x000000ff);
			if (((*(int *)&(status)) & 0177) != 0177 \
			&& ((*(int *)&(status)) & 0177) != 0)
				return (128 + ((*(int *)&(status)) & 0177));
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

int		execute(t_ast *ast, t_ast *head, t_env **env)
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
