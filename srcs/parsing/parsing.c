/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:06:39 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/03 14:54:33 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_pip	*ft_new_pipe(char *cmd)
{
	t_pip	*new;

	new = (t_pip *)malloc(sizeof(t_pip));
	if (!new)
		return (NULL);
	new -> cmd_pip = cmd;
	new -> prev = NULL;
	new -> next = NULL;
	return (new);
}

int	ft_index_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && i < ft_strlen(str))
	{
		if (i > 0 && str[i - 1] == '\\' && str[i] == '"')
		{
			i++;
			while (!(str[i - 1] == '\\' && str[i] == '"'))
				i++;
		}
		if (str[i] && str[i] == '\\')
			i++;
		if (i > 0 && str[i - 1] != '\\' && str[i] == '|')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_make_parse(t_sep *list)
{
	t_sep	*cur;
	char	*str;
	char	*str_new;

	cur = list;
	while (cur)
	{
		str = cur->cmd_sep;
		while (str)
		{
			if (ft_index_pipe(str) != -1)
			{
				str_new = ft_substr(str, 0, ft_index_pipe(str));	
				cur -> pipcell = ft_new_pipe(str_new);
				str+= ft_index_pipe(str);
				if (str_new)
					free(str_new);
			}
			str++;
		}
		cur = cur -> next;
	}
}
