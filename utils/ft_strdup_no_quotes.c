/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_without_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 12:48:43 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/06 13:06:25 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_no_quotes(char *s)
{
	size_t	i;
	char	*copy;

	copy = malloc(sizeof(char) * ft_strlen(s) - 1);
	if (copy == NULL)
		return (NULL);
	i = 1;
	while (s[i + 1] != '\0')
	{
		copy[i - 1] = s[i];
		i++;
	}
	copy[i - 1] = '\0';
	return (copy);
}
