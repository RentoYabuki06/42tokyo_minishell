/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:36:41 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/05 08:12:11 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	fd_run_echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	if (g_error != 1)
		g_status = 0;
	if (!args[i])
		ft_putchar_fd('\n', 1);
	flag = !ft_strncmp(args[i], "-n", 3) && ft_strlen(args[i]) == 2;
	if (flag)
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (1);
}
