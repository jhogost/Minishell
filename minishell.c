/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:28:30 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/19 12:28:30 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_lexer	*lexer;

	while (1)
	{
		lexer = NULL;
		line = (readline("chocolat shell: "));
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if ((ft_strcmp(line, "exit") == 0 && ft_strlen(line) == 4))
			break ;
		if (lexical(line, &lexer) == -42)
			return (free_line(line, &lexer), free_things(), 1);
		if (lexer)
			builtin_cmd_or_else(lexer->word);
		free_line(line, &lexer);
	}
	return (free_things(), free_line(line, &lexer), 0);
}
// TODO built in commands | struct for every var | chained list to get the
// order of what to do for each lines