/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:01:43 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/03 19:09:27 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_quote_error(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_status = 1;
	g_error = -1;
	return (-1);
}