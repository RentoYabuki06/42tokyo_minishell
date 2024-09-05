/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:37:20 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/05 09:36:26 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_remove_env(size_t index)
{
	// ここに環境変数を削除する処理を書く
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
		index = find_env(args[i]);
		if (index != -1)
		{
			if (g_envs[index])
				g_envs = remove_env(index);
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
