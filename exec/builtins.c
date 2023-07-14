/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:36:29 by yabad             #+#    #+#             */
/*   Updated: 2023/07/13 19:41:10 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	printf("execute echo\n");
}

void	ft_cd(t_cmd *cmd)
{
	printf("execute cd\n");
}

void	ft_pwd(t_cmd *cmd)
{
	printf("execute pwd\n");
}

void	ft_export(t_cmd *cmd)
{
	printf("execute export\n");
}

void	ft_unset(t_cmd *cmd)
{
	printf("execute unset\n");
}
