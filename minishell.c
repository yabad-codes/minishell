/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:01:45 by yabad             #+#    #+#             */
/*   Updated: 2023/07/28 10:23:20 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_mini_vars
{
	char	*input;
	char	*prompt;
	t_env	*env;
	int		savestdout;
	int		savestdin;
}	t_vars;

void	conductor(char *input, t_env **env)
{
	t_token	*tokens;
	t_ast	*ast;
	int		num;

	ast = NULL;
	tokens = lexer(input);
	num = 0;
	if (check_syntax_error(tokens))
	{
		ast = parser(tokens);
		if (!ast)
			return ;
		signal(SIGINT, SIG_IGN);
		handling_herdocs(ast, &num);
		if (g_data.atomic == false)
		{
			g_data.exit_status = execute(ast, ast, env);
			return ;
		}
		g_data.atomic = false;
	}
	free_ast(ast);
	return ;
}

static char	*custom_prompt(char *user)
{
	char	*prompt;
	char	*temp_prompt;

	prompt = ft_strjoin(user, "$ ");
	if (!prompt)
		prompt = ft_strdup("minishell$ ");
	temp_prompt = prompt;
	prompt = ft_strjoin(ANSI_COLOR_SKY_BLUE, temp_prompt);
	free(temp_prompt);
	temp_prompt = prompt;
	prompt = ft_strjoin(temp_prompt, ANSI_COLOR_RESET);
	free(temp_prompt);
	return (prompt);
}

int	func(int ac, char **av, char **envp)
{
	t_vars	v;

	(void)ac, (void)av;
	g_data.env = get_env(envp);
	v.prompt = custom_prompt(getenv("USER"));
	v.savestdout = dup(STDOUT_FILENO);
	v.savestdin = dup(STDIN_FILENO);
	while (TRUE)
	{
		handle_sig();
		v.input = readline(v.prompt);
		if (!v.input)
			break ;
		if (v.input[0])
		{
			add_history(v.input);
			conductor(v.input, &(g_data.env));
			dup2(v.savestdin, STDIN_FILENO);
			dup2(v.savestdout, STDOUT_FILENO);
		}
		free(v.input);
	}
	clear_env(g_data.env);
	free(v.prompt);
	return (g_data.exit_status);
}
