/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:29:48 by myokono           #+#    #+#             */
/*   Updated: 2024/09/03 12:16:22 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// 子プロセスが存在している時の処理
static void	child_process(int sign_num)
{
	if (!kill(g_pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_status = 131;
		}
		else if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_status = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_status = 1;
		prompt();
	}
}

// Ctrl+C（SIGINT）と Ctrl+\（SIGQUIT）に対応するシグナルハンドラー
// else if (sign_num == SIGQUIT)この時の挙動は何も起こらないらしい
void	signal_handler(int sign_num)
{
	if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_pid != 0)
		child_process (sign_num);
	else
	{
		if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_status = 1;
			prompt();
		}
		else if (sign_num == SIGQUIT)
		{
			// ft_putstr_fd("\b\b  \b\b", 1);
		}
	}
}

// sigactionを使ってシグナルハンドラーを設定
void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;      // ハンドラー関数を指定
	sigemptyset(&sa.sa_mask);            // 他のシグナルをブロックしない
	sa.sa_flags = SA_RESTART;            // システムコールを再開する

	sigaction(SIGINT, &sa, NULL);        // SIGINTに対してハンドラーを設定
	sigaction(SIGQUIT, &sa, NULL);       // SIGQUITに対してハンドラーを設定
}

