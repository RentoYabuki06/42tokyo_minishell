/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:37:30 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/05 09:29:15 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void ft_modify_env(char *str, size_t index_equal, size_t index_env)
{
	size_t	index_env_key;
	char 	*key_varenv;
	char 	*value_varenv;

	index_env_key = ft_strchr_index(g_envs[index_env], '=');
	if (index_env_key == -1)
		g_envs[index_env] = str;
	else
	{
		free(g_envs[index_env]);
		key_varenv = ft_substr(str, 0, index_equal);
		value_varenv = ft_substr(str, index_equal + 1, ft_strlen(str) - index_equal);
		g_envs[index_env] = ft_strjoin_minishell(key_varenv, "=\"", value_varenv, "\"");
		if (!key_varenv)
			free(key_varenv);
		if (!value_varenv)
			free(value_varenv);
	}
	return ;
}

static void ft_add_env(char *str, size_t index_equal)
{
	size_t	count;
	char 	*key_varenv;
	char	*value_varenv;

	count = ft_get_envs_count();
	g_envs = ft_realloc_envs(count + 1);
	key_varenv = ft_substr(str, 0, index_equal);
	if (index_equal == ft_strlen(str))
		g_envs[count] = *key_varenv;
	else
	{
		value_varenv = ft_substr(str, index_equal + 1, ft_strlen(str) - index_equal);
		g_envs[count] = ft_strjoin(key_varenv, value_varenv);
		if (value_varenv)
			free(value_varenv);
	}
	if (key_varenv)
		free(key_varenv);
	return ;
}

static void ft_update_env(char **args, size_t i)
{
	size_t	index_equal;
	size_t	index_env;
	char	*key_varenv;

	index_equal = ft_strchr_index(args[i], '=');
	if (index_equal == -1)
		index_equal = ft_strlen(args[i]);
	key_varenv = ft_substr(args[i], 0, index_equal);
	index_env = ft_find_env(key_varenv);
	if (key_varenv)
		free(key_varenv);
	if (index_env == -1)
		ft_add_env(args[i], index_equal);
	else
		ft_modify_env(args[i], index_equal,  index_env);
	return ;
}

int	ft_run_export(char **args)
{
	size_t	i;

	i = 0;
	g_status = 0;
	if (!args[1])
	{
		while (g_envs[i])
		{
			ft_putstr_fd("declare -x: ", 2);
			ft_putstr_fd(g_envs[i], 2);
			ft_putchar_fd('\n', 2);
			i++;
		}
		return (1);
	}
	while (args[i])
	{
		if (!args[i] || !args[i][0] || args[i][0] == '=')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_status = 1;
		}
		else 
			ft_update_env(args, i);
		i++;
	}
	return (1);
}
