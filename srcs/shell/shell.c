/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:23:25 by myokono           #+#    #+#             */
/*   Updated: 2024/09/03 10:27:34 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	interactive_shell(void)
{
	char	*line;
	
	// 初期化する
	line = readline(NULL);
	while (line)
	{
		free_and_null (line);
		line = readline(NULL);
	}
	ft_putstr_fd("exit\n ", 1);
	return (0);
}



// 初期化関数


void	non_interactive_shell(char *line)
{
	
}