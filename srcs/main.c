/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:41:49 by myokono           #+#    #+#             */
/*   Updated: 2024/09/02 21:17:06 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// エラーメッセージの表示関数
int	error_msg (char *cmd, char *msg, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	g_status = status;
	return (0);
}

// エグジット関数（アレンジ）
void free_and_exit ()
{
	
}

// メイン関数
// コマンドライン引数の確認とループ関数の開始
int	main (int argc, char **argv, char **env)
{
	// 環境変数をリストでコピーして使用する方が良いのかgetenvでそれぞれ使用する方が良いのか確認して実装する
	if (ft_strncmp(argv[1], "-c", 3) == 0)
	{
		if (argv[2])
			return (non_interactive_shell(argv[2]));
		else if (argc == 2)
			error_msg (argv[1], ": option requires an argument", 2);
	}
	else if (argc > 1)
		error_msg(argv[1], ": No such file or directory", 127);
	else
		interactive_shell();

	return (0);
}
