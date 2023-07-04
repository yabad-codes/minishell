/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:15:11 by yabad             #+#    #+#             */
/*   Updated: 2023/07/04 22:33:00 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	add_cmd_arg(char ***cmd_arg, char *new)
{
	char	**new_cmd_arg;
	char	**tmp;
	int		i;

	i = ft_arrlen(*cmd_arg);
	tmp = *cmd_arg;
	new_cmd_arg = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_cmd_arg)
	{
		// free tokens
		exit(1);
	}
	ft_memcpy(new_cmd_arg, *cmd_arg, sizeof(char *) * i);
	new_cmd_arg[i] = ft_strdup(new);
	new_cmd_arg[i + 1] = NULL;
	free(tmp);
	*cmd_arg = new_cmd_arg;
}
