/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:28:53 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/19 12:28:53 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_splitted(char **splitted)
{
	int	i;

	if (!splitted)
		return ;
	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	free_line(char *line, t_lexer **lexer)
{
	t_lexer	*tmp;
	t_lexer	*next;

	if (line)
		free(line);
	if (lexer && *lexer)
	{
		tmp = *lexer;
		while (tmp)
		{
			next = tmp->next;
			free(tmp->word);
			free(tmp->whole_line);
			free(tmp);
			tmp = next;
		}
		*lexer = NULL;
	}
}

void	free_things(void)
{
	rl_clear_history();
}
// TODO update whenever the struct is ready to free everything