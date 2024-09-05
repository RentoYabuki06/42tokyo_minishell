/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 08:45:28 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/05 08:49:03 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strchr_index(const char *s, int c)
{
	int		i;
	char	pc;

	i = 0;
	pc = c;
	while (s[i])
	{
		if (s[i] == pc)
		{
			return (i);
		}
		i++;
	}
	if (s[i] == pc)
		return (i);
	return (-1);
}
