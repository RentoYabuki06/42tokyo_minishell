/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:23:25 by myokono           #+#    #+#             */
/*   Updated: 2024/09/03 15:33:47 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init (t_copy *cmdline)
{
	char	*tmp;
	size_t	shlvl;

	ft_bzero(cmdline, sizeof(t_copy));
	tmp = get_env("SHLVL");
	shlvl = (ft_atoi(tmp) + 1);
	free(tmp);
	tmp = ft_itoa(shlvl);
	set_env("SHLVL", tmp);
	free(tmp);
	prompt();
	g_pid = 0;
	// g_tester = 0;
}

static void	minishell(t_copy *cmdline, char *line)
{
	size_t	i;

	// スプリットについては後で考える
	cmdline->cmdssep = ft_minishell_split(line, ';');
	i = 0;
	while (cmdline->cmdssep[i])
	{
		cmdline->list = add_cell(cmdline->list, cmdline->cmdssep[i], i);
		i++;
	}
	parse_pip(cmdline->list);
	execute_commands(cmdline->list, cmdline);
	if (cmdline->list)
		free_list(&cmdline->list);    //////////////////////////////
	if (cmdline->cmdssep)
		free_and_null(&cmdline->cmdssep);   /////////////////////////////
}


int	check_line (char	*line)
{
	// スペースとコロンの確認→要確認
		return (0);
	// パイプとセミコロンの確認（レンレン）
	if ()
		return (0);
	return (1);
}

void	shell(char *line, int interactive)
{
	t_copy	cmdline;

	setup_signal_handlers();
	init(&cmdline);
	while (1)
	{
		if (interactive)
		{
			line = readline(NULL);
			if (line == NULL)
				break ;
		}
		cmdline.list = NULL;
		cmdline.cmdssep = NULL;
		if (check_line(line))
			minishell(&cmdline, line);
		free_and_null(line);
		if (interactive)
			prompt();
		if (!interactive)
			free_and_exit(&cmdline);
	}
	ft_putstr_fd("exit\n", 1);
	free_and_exit(&cmdline);
}
