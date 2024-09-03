/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:58:24 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/03 19:26:43 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_double_quote(t_copy *copy, int j)
{
	if (copy->i == (int)ft_strlen(copy->wc) - 1)
		return (ft_quote_error('"'));
	while (copy->wc[copy->i] && copy->wc[++copy->i] != '"')
	{
		j = 0;
		if (copy->wc[copy->i - 1] != '\\' && copy->wc[copy->i] == '$')
			j = ft_env(copy, 0, 0, 0);
		if (copy->wc[copy->i] == '\\')
			copy->i++;
		if (j != 1)
			copy->cmd[++copy->j] = copy->wc[copy->i];
	}
	if (copy->wc[copy->i] == '"' && (copy->wc[copy->i + 1] == ' ' || copy->wc[copy->i + 1] == '\0') && !copy->cmd[0])
    copy->cmd[0] = '\0';
	if ((copy->i == (int)ft_strlen(copy->wc)) && copy->wc[copy->i] != '"')
    return (ft_quote_error('"'));
	copy->i++;
	if (copy->cmd[0] == '\0' && (copy->wc[copy->i] == ' ' || copy->wc[copy->i] == '\0'))
		return (1); 
	return (-2);
}