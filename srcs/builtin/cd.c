/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:36:07 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/05 07:59:11 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_set_directory(char *path, int home)
{
	struct stat	st;  // 指定されたパスの情報を格納する構造体

	// ディレクトリの変更を試みる
	if (change(path, home))
		return (1);  // 成功した場合、1を返す

	// ディレクトリ変更に失敗した場合、エラーメッセージを表示
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	g_status = 1;  // エラーステータスを設定

	// パスの情報を取得
	if (stat(path, &st) == -1)
	{
		ft_putstr_fd(": No such file or directory", 2);  // パスが存在しない場合のエラーメッセージ
		g_status = 127;  // コマンドが見つからなかった場合のステータス
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);  // パーミッションが無い場合のエラーメッセージ
	else
		ft_putstr_fd(": Not a directory", 2);  // ディレクトリではない場合のエラーメッセージ
	ft_putchar_fd('\n', 2);  // 改行文字を出力

	// `home` が真の場合、パスを解放
	if (home)
		free(path);
	return (1);  // 失敗した場合、1を返す
}

int	run_cd(char **args)
{
	char	*home;

	g_status = 0;
	if (args && args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!args[1] || ft_strncmp(args[1], "~", 1) || ft_strncmp(args[1], "--", 2))
	{
		if (!(home = ft_get_env("HOME")))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		return (ft_set_directory(ft_get_env("HOME"), 1));
	}
	args[1] = ft_add_home_path(args[1]);
	if (ft_strncmp(args[1], "-", 1))
	{
		if (ft_get_env("OLDPWD"))
			ft_set_directory(ft_get_env("OLDPWD"), 0);
		if (ft_get_env("PWD"))
		{
			ft_putstr_fd(ft_get_env("PWD"), 1);
			ft_putchar_fd('\n', 1);
		}
		return (1);
	}
	return (ft_set_directory(args[1], 0));
}
