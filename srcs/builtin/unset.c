/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:37:20 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/05 13:27:25 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_remove_env(size_t index)
{
	size_t	num_env;
	char 	*tmp;

	num_env = ft_envs_count(g_envs);
	while (g_envs[index + 1])
	{
		tmp = ft_strdup(g_envs[index + 1]);
		free(g_envs[index]);
		g_envs[index] = tmp;
		index++;
	}
	return (ft_realloc_envs(num_env - 1));
}

int	ft_run_unset(char **args)
{
	size_t	i;
	size_t	index;

	g_status = 0;
	if (!args[1])
		return (1);
	i = 0;
	while (args[++i])
	{
		index = ft_find_env(args[i]);
		if (index != -1)
		{
			if (g_envs[index])
				g_envs = ft_remove_env(index);
		}
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_status = 1;
		}
	}
	return (1);
}
