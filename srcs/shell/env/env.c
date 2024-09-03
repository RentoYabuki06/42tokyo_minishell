/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:49:30 by myokono           #+#    #+#             */
/*   Updated: 2024/09/03 19:12:46 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_get_path(void)
{
	char	**path;
	char	*tmp;

	tmp = getenv("PATH");
	if (!tmp)
		return (NULL);
	path = ft_split(tmp, ':');
	return (path);
}


size_t	ft_get_envs_count(void)
{
	size_t	count;

	count = 0;
	while (g_envs[count])
		count++;
	return (count);
}

char	**ft_realloc_envs(size_t size)
{
	char	**new;
	size_t	i;

	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);

	i = 0;
	while (g_envs[i] && i < size)
	{
		new[i] = ft_strdup(g_envs[i]);
		i++;
	}
	new[size] = 0;
	ft_free_array(g_envs);
	return (new);
}

ssize_t find_env(char *env)
{
	char	*sub;
	ssize_t i;
	ssize_t index;

	if (!env)
		return (-1);
	i = 0;
	sub = NULL;
	while (g_envs[i])
	{
		if ((index = ft_get_char_by_index(g_envs[i], '=')) == -1)
			index = ft_strlen(g_envs[i]);
		if ((sub = ft_substr(g_envs[i], 0, index)))
		{
			if (ft_strequ(sub, env))
			{
				free(sub);
				return (i);
			}
			free(sub);
		}
		i++;
	}
	return (-1);
}
