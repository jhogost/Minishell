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

void	print_lexer(t_token *lexer)
{
	while (lexer)
	{
		if (lexer->type == 0)
			printf("Type: WORD ");
		if (lexer->type == 1)
			printf("Type: PIPE ");
		if (lexer->type == 2)
			printf("Type: OR ");
		if (lexer->type == 3)
			printf("Type: REDIR_IN ");
		if (lexer->type == 4)
			printf("Type: REDIR_OUT ");
		if (lexer->type == 5)
			printf("Type: APPEND ");
		if (lexer->type == 6)
			printf("Type: HEREDOC ");
		if (lexer->type == 7)
			printf("Type: AND ");
		printf("word: [%s]\n", lexer->word);
		lexer = lexer->next;
	}
}

int	main(void)
{
	char	*line;
	t_token	*lexer;

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
		lexer = build_lexer(line, lexer);
		if (!lexer)
			return (free_things(), free_line(line, &lexer), 1);
		if (lexer)
			builtin_cmd_or_else(lexer->word);

		print_lexer(lexer);

		free_line(line, &lexer);
	}
	return (free_things(), free_line(line, &lexer), 0);
}
// TODO built in commands | struct for every var | chained list to get the
// order of what to do for each lines
