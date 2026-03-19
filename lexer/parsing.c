/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:19:34 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/19 17:18:57 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char *word)
{
	if (!word)
		return (0);
	if (ft_countchar(word, '|') > 2)
		return (-1);
	if (ft_countchar(word, '>') > 2)
		return (-1);
	if (ft_countchar(word, '&') > 2)
		return (-1);
	if (ft_countchar(word, '<') > 2)
		return (-1);
	return (0);
}
