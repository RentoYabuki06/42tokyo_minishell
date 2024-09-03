/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:20:33 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/03 18:56:12 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_exec_cmd(t_copy *copy, int j)
{
    while (copy->wc[copy->i] && copy->wc[copy->i] != ' ')
    {
        j = -2;
        if ((copy->wc[copy->i] == '1' || copy->wc[copy->i] == '2') && copy->wc[copy->i + 1] == '>' && (!copy->cmd[0] || copy->wc[copy->i - 1] == ' '))
            copy->i++;
        while (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"')
        {
            while (copy->wc[copy->i] == '"')
            {
                j = ft_double_quote(copy, j);
                if (j == -1)
                    return (NULL);
            }
            // シングルクォート ('') の処理
            while (copy->wc[copy->i] == '\'')
            {
                j = ft_single_quote(copy);
                if (j == -1)
                    return (NULL);
            }
        }
        if (copy->wc[copy->i] == '\\')
            copy->i++;
        if (copy->wc[copy->i] && copy->wc[copy->i] == '$' && (copy->i == 0 || copy->wc[copy->i - 1] != '\\'))
        {
            if (copy->wc[copy->i + 1] == '\\')  // $ の後に \ がある場合
                copy->cmd[++copy->j] = copy->wc[copy->i];  // そのまま文字列に追加
            else
                j = ft_env(copy, 0, 0, 1);  // 環境変数の展開を実行
        }
        if ((copy->wc[copy->i] == '>' || copy->wc[copy->i] == '<') && (copy->i == 0 || copy->wc[copy->i - 1] != '\\'))
            j = ft_redirection(copy, 0);

        // 空白で区切られた場合の処理
        if ((copy->wc[copy->i] == ' ' && copy->wc[copy->i - 1] != '\\')
            && (copy->cmd[0] || (!copy->cmd[0] && (copy->wc[copy->i - 1] == '"'
                        || copy->wc[copy->i - 1] == '\'') && (copy->wc
                        [copy->i - 2] == '"' || copy->wc[copy->i - 2] == '\''
                        || j == 1))))
            break ;  // 空白で区切られたらループを抜ける
        
        // $ が無効化された場合や、$ 以外の文字を処理する場合
        if (copy->i < (int)ft_strlen(copy->wc) && ((copy->wc[copy->i] == '$'
            && (copy->i == 0 || copy->wc[copy->i - 1] == '\\'))
            || (copy->wc[copy->i] != '$' && j == -2)))
            copy->cmd[++copy->j] = copy->wc[copy->i];
        if (copy->i < (int)ft_strlen(copy->wc))
            copy->i++;
    }
	copy->cmd[copy->j + 1] = 0;
	return (copy->cmd);
}

char *ft_main_parsing(char *whole_cmd, t_copy *copy)
{
    copy->i = 0;
    copy->j = -1;
    copy->cmd = NULL;
    copy->args = NULL;
    copy->redir.sstdout = 1;
    copy->redir.sstderr = 2;
    copy->redir.sstdin = 1; 
    copy->redir.out1 = NULL;
    copy->redir.out2 = NULL;
    copy->redir.in = NULL;
    copy->wc = whole_cmd;
    g_error = 0;
	copy->cmd = (char *)malloc(sizeof(char) * (ft_strlen(whole_cmd) + 1));
	if (!(copy->cmd))
		return (NULL);
	copy->cmd[0] = 0;
	while (copy->wc[copy->i] && copy->wc[copy->i] != ' ')
		copy->i++;
	if (!ft_exec_cmd(copy, 0) || g_error == - 1)
		return (NULL);
	copy->args = (char **)malloc(sizeof(char *) * 1);
	if (!(copy->args) || ft_options(copy, 1, 0) == -1)
		return (NULL);
	return (copy->cmd);
}

