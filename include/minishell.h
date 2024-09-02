/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:20:58 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/02 14:25:33 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include "../utils/libft/libft.h"

/*
** グローバル変数の定義
** シェル全体で使用される環境変数やステータスコードを格納する変数です。
*/
char					**g_envs;  // 環境変数のリスト
pid_t					g_pid;    // プロセスID
int						g_error;  // エラーステータス
int						g_status; // コマンドの終了ステータス
int						g_tester; // テストモードで使用するステータス

/*
** データ構造の定義
** シェルコマンドを解析して構造化するための各種構造体を定義しています。
*/

// 各構造体が次のコマンド区切りや前の区切りを指し示すことで、リストとしてコマンドの流れを管理できるようになります。

typedef	struct			s_sep
{
	char				*cmd_sep;  // コマンド区切り文字列
	struct s_sep		*prev;     // 前の要素へのポインタ
	struct s_sep		*next;     // 次の要素へのポインタ
	struct s_pip		*pipcell;  // パイプコマンドへのポインタ
}						t_sep;

// パイプで繋がった複数のコマンドを管理します。各コマンドの間でデータを渡す処理や、パイプを使った並列実行を可能にするためのデータ構造を提供します。
// パイプの前後のコマンドを指し示すことで、パイプラインを構築し、コマンドの実行を連続して行えるようになります。
typedef	struct			s_pip
{
	char				*cmd_pip;  // パイプで接続されるコマンド文字列
	struct s_pip		*prev;     // 前のパイプコマンドへのポインタ
	struct s_pip		*next;     // 次のパイプコマンドへのポインタ
}						t_pip;


// リダイレクトの種類や対象ファイル、リダイレクトの状態（成功・失敗など）を管理します。
// これにより、シェルがリダイレクトを正しく処理し、ファイルへの入出力操作を行えるようになります。
typedef	struct			s_redir
{
	char				*out1;     // 出力リダイレクト1
	char				*out2;     // 出力リダイレクト2
	char				*in;       // 入力リダイレクト
	int					sstdout;   // 標準出力のファイルディスクリプタ
	int					sstderr;   // 標準エラー出力のファイルディスクリプタ
	int					sstdin;    // 標準入力のファイルディスクリプタ
	int					end;       // リダイレクトの終了フラグ
	int					i;         // リダイレクト操作のインデックス
	char				*name;     // リダイレクト対象のファイル名
	char				*value;    // 環境変数の値
}						t_redir;

// これらの処理の中間結果を保持し、コマンドの解析と実行をスムーズに進めるためのデータ構造を提供します。
// 特に、コマンドや引数のリスト、リダイレクト情報などをまとめて扱うことで、シェルの機能を統合的に管理します。

typedef struct			s_copy
{
	t_sep				*list;     // コマンドのリスト
	char				**cmdssep; // コマンド分割結果の配列
	char				*wc;       // ワイルドカード
	char				**args;    // コマンドの引数
	char				*cmd;      // コマンド文字列
	int					i;         // インデックス
	int					j;         // インデックス
	t_redir				redir;     // リダイレクト構造体
	char				**tmp;     // 一時的な引数の配列
	char				*arg;      // 引数の文字列
}						t_copy;


void					loop(void);
void					loop_tester(char *line);

#endif