/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:01:45 by yabad             #+#    #+#             */
/*   Updated: 2023/07/18 20:15:41 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		execute(ast, ast, env);
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
	char	*input;
	char	*prompt;
	t_env	*env;

	(void)ac, (void)av;
	env = get_env(envp);
	prompt = custom_prompt(getenv("USER"));
	while (TRUE)
	{
		input = readline(prompt);
		if (!input)
			break ;
		if (ft_strncmp(input, "\n", ft_strlen(input)))
		{
			add_history(input);
			conductor(input, &env);
		}
		free(input);
	}
	return (0);
}
