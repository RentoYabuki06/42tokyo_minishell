/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:25:58 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/03 19:29:05 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	s_quote(t_copy *copy)
{
	if (copy->i == ((int)ft_strlen(copy->wc) - 1))
		return (ft_quote_error('\''));
	if (copy->wc[copy->i + 1] == '\'' && (copy->wc[copy->i + 2] == ' '
			|| copy->wc[copy->i + 2] == '\0'))
		copy->cmd[++copy->j] = '\0';
	while (copy->wc[copy->i] && copy->wc[++copy->i] != '\'')
		copy->cmd[++copy->j] = copy->wc[copy->i];
	if ((copy->i == (int)ft_strlen(copy->wc)) && copy->wc[copy->i] != '\'')
		return (ft_quote_error('\''));
	copy->i++;
	return (-2);
}