/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:43:58 by yabad             #+#    #+#             */
/*   Updated: 2023/07/13 10:57:44 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"

/**
 * @brief The starting point of execution
 * @param ast Our tree
*/
void	execute(t_ast *ast, t_ast *head);
char	*get_path(char *cmd);
#endif