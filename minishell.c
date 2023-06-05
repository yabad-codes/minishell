/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:01:45 by yabad             #+#    #+#             */
/*   Updated: 2023/06/05 15:40:18 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)ac, (void)av, (void)env;
	while (TRUE)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (ft_strncmp(input, "\n", ft_strlen(input)))
		{
			add_history(input);
			printf("input : %s\n", input);
		}
		free(input);
	}
	return (0);
}
