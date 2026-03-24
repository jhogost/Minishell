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
			printf("Type: WORD \t");
		if (lexer->type == 1)
			printf("Type: PIPE \t");
		if (lexer->type == 2)
			printf("Type: OR \t");
		if (lexer->type == 3)
			printf("Type: REDIR_IN \t");
		if (lexer->type == 4)
			printf("Type: REDIR_OUT ");
		if (lexer->type == 5)
			printf("Type: APPEND \t");
		if (lexer->type == 6)
			printf("Type: HEREDOC \t");
		if (lexer->type == 7)
			printf("Type: AND \t");
		printf("word: [%s]\n", lexer->word);
		lexer = lexer->next;
	}
}

int	main_loop(t_token **lexer, char *line)
{
	if (*line)
		add_history(line);
	if (verify_line(line) == -42)
		return (0);
	if ((ft_strcmp(line, "exit") == 0 && ft_strlen(line) == 4))
		return (-42);
	*lexer = build_lexer(line, *lexer);
	if (!*lexer)
		return (-42);
	builtin_cmd_or_else((*lexer)->word);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*lexer;
	t_shell	shell;

	if (argc != 1)
		return (printf("Usage: ./minishell\n"), argv++, 1);
	if (init_struct(&shell, envp) == -42)
		return (1);
	while (1)
	{
		setup_signals();
		lexer = NULL;
		line = (readline("chocolat shell: "));
		if (!line)
			return (free_everything(&shell, line, &lexer), 1);
		if (main_loop(&lexer, line) == -42)
			break ;
		print_lexer(lexer);
		free_line(line, &lexer);
	}
	return (free_everything(&shell, line, &lexer), 0);
}
// TODO built in commands | struct for every var | chained list to get the
// order of what to do for each lines
