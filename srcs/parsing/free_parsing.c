/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:03:04 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/03 15:10:41 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_cmdarg(t_copy *copy)
{
	int i;

	i = 0;
	if (!copy)
		return ;
	if (copy->cmd)
		free(copy->cmd);
	if (copy->arg)
	{
		while (copy->arg[i++])
			free(copy->arg[i]);
		free(copy->arg);
	}
	if (copy->redir.out1)
		free(copy->redir.out1);
	if (copy->redir.out2)
		free(copy->redir.out2);
	if (copy->redir.in)
		free(copy->redir.in);
	copy-> cmd = NULL;
	copy-> arg = NULL;
	copy-> redir.out1 = NULL;
	copy-> redir.out2 = NULL;
	copy-> redir.in = NULL;
}

void	ft_free_pipe(t_pip *pip)
{
	t_pip	*tmp;

	if (!pip)
		return ;
	while (pip)
	{
		tmp = pip;
		if (tmp->cmd_pip)
			free(tmp->cmd_pip);
		pip = pip->next;
		free(tmp);
	}
	pip = NULL;
}

void	ft_free_list(t_sep *list)
{
	t_sep	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		if (tmp->cmd_sep)
			free(tmp->cmd_sep);
		if (tmp->pipcell)
			ft_free_pipe(tmp->pipcell);
		list = list->next;
		free(tmp);
	}
	list = NULL;
}