/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:18:51 by jbayet            #+#    #+#             */
/*   Updated: 2026/03/20 20:00:04 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *s, int start, size_t len)
{
	char	*subdup;
	size_t	size_len;
	size_t	i;

	size_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > size_len - start)
		len = size_len - start;
	subdup = malloc(sizeof(char) * (len + 1));
	if (!subdup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subdup[i] = s[start + i];
		i++;
	}
	subdup[i] = '\0';
	return (subdup);
}
