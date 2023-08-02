/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabad <yabad@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:44:54 by yabad             #+#    #+#             */
/*   Updated: 2023/07/27 20:58:10 by yabad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_LEN 19

static bool	compare(const char *str, const char *value)
{
	while (*str)
	{
		if (*str > *value)
			return (false);
		else if (*str < *value)
			return (true);
		str++;
		value++;	
	}
	return (true);
}

static bool	is_greater(const char *str, char sign)
{
	char	*max;
	char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	if (sign == '+' || sign == 0)
		return (compare(str, max));
	return (compare(str, min));
}

static bool	exceeds_max(const char *str)
{
	int		len;
	char	sign;

	sign = 0;
	if (*str == '-' || *str == '+')
	{
		sign = *str;
		str++;
	}
	len = ft_strlen(str);
	if (len < MAX_LEN)
		return (false);
	else if (len > MAX_LEN)
		return (true);
	else
		return (!is_greater(str, sign));
	return (false);
}

bool	is_digit(char *str)
{
	if (exceeds_max(str))
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!(*str <= '9' && *str >= '0'))
			return (false);
		str++;
	}
	return (true);
}
