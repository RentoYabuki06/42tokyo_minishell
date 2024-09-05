/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:25:03 by yabukirento       #+#    #+#             */
/*   Updated: 2024/09/05 09:26:41 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_minishell(char const *s1, char const *s2, char const *s3, char const *s4)
{
	char	*ans;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_s3;
	size_t	len_s4;

	if (!s1 || !s2 || !s3 || !s4)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_s3 = ft_strlen(s3);
	len_s4 = ft_strlen(s4);
	ans = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + len_s3 + len_s4 + 1));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, s1, len_s1 + 1);
	ft_strlcpy(ans + len_s1, s2, len_s2 + 1);
	ft_strlcpy(ans + len_s1 + len_s2, s3, len_s3 + 1);
	ft_strlcpy(ans + len_s1 + len_s2 + len_s3, s4, len_s4 + 1);
	return (ans);
}
