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

int	run_interactive(t_shell *shell)
{
	shell->lexer = NULL;
	shell->cmds = NULL;
	shell->input = (readline("chocolat shell: "));
	if (!shell->input)
		return (-42);
	if (*shell->input)
		add_history(shell->input);
	if (verify_line(shell->input) == -42)
		return (free_interactive(shell), 1);
	if ((ft_strcmp(shell->input, "exit") == 0 && ft_strlen(shell->input) == 4))
		return (0);
	shell->lexer = build_lexer(shell->input, shell->lexer);
	if (!shell->lexer)
		return (-42);
	builtin_cmd_or_else((shell->lexer)->word);
	print_lexer(shell->lexer);
	free_interactive(shell);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		loop_value;

	if (argc != 1)
		return (printf("Usage: ./minishell\n"), argv++, 1);
	if (init_struct(&shell, envp) == -42)
		return (free_everything(&shell), 1);
	setup_signals();
	while (1)
	{
		loop_value = run_interactive(&shell);
		if (loop_value == -42)
			return (free_everything(&shell), 1);
		if (loop_value == 1)
			continue ;
		else
			break ;
	}
	return (free_everything(&shell), 0);
}
// TODO built in commands | struct for every var | chained list to get the
// order of what to do for each lines
