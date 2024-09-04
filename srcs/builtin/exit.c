/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:37:14 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/05 07:58:58 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

// 本家のexitコマンドはint型以上でも入力できるので、後から修正が必要かも
static int	ft_exit_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	ans;

	ans = 0;
	sign = 1;
	i = ft_sign(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((ans > (INT64_MAX / 10))
			|| (ans == (INT64_MAX / 10) && (str[i] >= '8' && str[i] <= '9')))
		{
			if (sign == 1)
				return (-1);
			if (sign == -1)
				return (0);
		}
		ans *= 10;
		ans += str[i] - '0';
		i++;
	}
	return (((long long)ans * sign)  % 256);
}


int	fd_run_exit(char **args, t_copy copy)
{
	size_t	i;

	i = 1;
	g_status = 0;
	if (!args[i])
		ft_exit(copy);
	while (args[++i])
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_status = 1;
	}
	if (ft_exit_atoi(args[i]))
		g_status = ft_exit_atoi(args[i]);
	else 
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_status = 2;
	}
	ft_exit(copy);
}
