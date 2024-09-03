/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:41:49 by myokono           #+#    #+#             */
/*   Updated: 2024/09/04 07:47:54 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// エラーメッセージの表示関数
int	ft_error_msg (char *cmd, char *msg, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	g_status = status;
	return (0);
}

// エグジット関数（アレンジ）
void	ft_exit (t_copy *copy)
{
	free_cmdarg(copy);
	if (g_envs)
		ft_free_array(g_envs);
	if (copy->list)
		free_list(copy->list);
	if (copy->cmdssep)
		free(copy->cmdssep);
	if (!g_tester)
		ft_putstr_fd("exit\n", 2);
	exit(g_status);
}


// メイン関数
// コマンドライン引数の確認とループ関数の開始
int	main (int argc, char **argv, char **env)
{
	// 環境変数をリストでコピーして使用する方が良いのかgetenvでそれぞれ使用する方が良いのか確認して実装する
	if (argc > 1 && ft_strncmp(argv[1], "-c", 3) == 0)
	{
		if (argv[2])
			ft_minishell(argv[2], 0);
		else if (argc == 2)
			ft_error_msg (argv[1], ": option requires an argument", 2);
	}
	else if (argc > 1)
		ft_error_msg(argv[1], ": No such file or directory", 127);
	else
		ft_minishell(NULL, 1);

	return (0);
}
