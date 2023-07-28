/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:15:11 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:59:44 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(EXIT_FAILURE);
	i = 0;
	if (tmp)
	{
		i = -1;
		while (tmp[++i])
			new_cmd_arg[i] = tmp[i];
	}
	new_cmd_arg[i] = new;
	new_cmd_arg[i + 1] = NULL;
	free(tmp);
	*cmd_arg = new_cmd_arg;
}
