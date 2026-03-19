/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:55:52 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/10 16:55:52 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_line(char **line, t_shell **lexer)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		free(line[i]);
		i++;
	}
	free(line);
	while (*lexer)
	{
		t_shell *temp = *lexer;
		*lexer = (*lexer)->next;
		free(temp->word);
		free(temp);
	}
}

void	free_things(void)
{
	rl_clear_history();
}
//TODO update whenever the struct is ready to free everything