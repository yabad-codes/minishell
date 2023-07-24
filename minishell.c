/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:01:45 by yabad             #+#    #+#             */
/*   Updated: 2023/07/24 12:34:48 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		handling_herdocs(ast, &num);
		g_exit_status = execute(ast, ast, env);
	}
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

int	main(int ac, char **av, char **envp)
{
	t_vars	v;

	(void)ac, (void)av;
	v.env = get_env(envp);
	v.prompt = custom_prompt(getenv("USER"));
	v.savestdout = dup(STDOUT_FILENO);
	v.savestdin = dup(STDIN_FILENO);
	while (TRUE)
	{
		v.input = readline(v.prompt);
		if (!v.input)
			break ;
		if (ft_strncmp(v.input, "\n", ft_strlen(v.input)))
		{
			add_history(v.input);
			conductor(v.input, &v.env);
			dup2(v.savestdin, STDIN_FILENO);
			dup2(v.savestdout, STDOUT_FILENO);
		}
		free(v.input);
	}
	return (0);
}
