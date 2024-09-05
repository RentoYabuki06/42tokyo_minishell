/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:36:50 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/05 09:34:56 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_run_env()
{
	size_t	i;

	i = 0;
	g_status = 0;
	while (g_envs[i])
	{
		if (ft_strchr(g_envs[i], '='))
		{
			ft_putstr_fd(g_envs[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
}
