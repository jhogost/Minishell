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

/* void	print_lexer(t_token *lexer)
{
	printf("LEXER :\n");
	while (lexer)
	{
		if (lexer->type == 0)
			printf("Type: WORD \t\t");
		if (lexer->type == 1)
			printf("Type: BUILTIN \t\t");
		if (lexer->type == 2)
			printf("Type: PIPE \t\t");
		if (lexer->type == 3)
			printf("Type: OR \t\t");
		if (lexer->type == 4)
			printf("Type: REDIR_IN \t\t");
		if (lexer->type == 5)
			printf("Type: REDIR_OUT \t");
		if (lexer->type == 6)
			printf("Type: APPEND \t\t");
		if (lexer->type == 7)
			printf("Type: HEREDOC \t\t");
		if (lexer->type == 8)
			printf("Type: AND \t\t");
		printf("word: [%s]\n", lexer->word->str);
		lexer = lexer->next;
	}
	printf("\n");
}

void	print_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*redir_tmp;

	i = 0;
	printf("CMD :\n");
	while (cmd->argv[i])
	{
		printf("%s\n", cmd->argv[i]);
		i++;
	}
	printf("pipe in: %d\n", cmd->pipe[0]);
	printf("pipe out %d\n", cmd->pipe[1]);
	redir_tmp = cmd->redir;
	while (redir_tmp)
	{
		printf("REDIR\n");
		if (redir_tmp->type)
			printf("\tredir type: %d\n", redir_tmp->type);
		if (redir_tmp->file)
			printf("\tfile content: %s\n", redir_tmp->file);
		if (redir_tmp->heredoc_content)
			printf("\theredoc content: %s\n", redir_tmp->heredoc_content);
		redir_tmp = redir_tmp->next;
	}
	printf("\n");
} */

static void	set_error_signal(t_shell *shell)
{
	shell->exit_code = 130;
	g_last_signal = 0;
}

static void	new_read_line(t_shell *shell)
{
	shell->lexer = NULL;
	shell->cmds = NULL;
	shell->input = (readline("☕ chocolat shell: "));
	shell->count_line++;
}

int	run_interactive(t_shell *shell)
{
	new_read_line(shell);
	if (!shell->input)
		return (-42);
	if (g_last_signal == 130)
		shell->exit_code = 130;
	if (shell->input[0] == '\0' || blank_line(shell->input) == 1)
		return (free_interactive(shell), 1);
	if (*shell->input)
		add_history(shell->input);
	if (verify_line(shell->input, shell) == -42)
		return (free_interactive(shell), 1);
	if ((ft_strcmp(shell->input, "exit") == 0 && ft_strlen(shell->input) == 4))
		return (0);
	shell->lexer = build_lexer(shell->input, shell->lexer);
	if (!shell->lexer)
		return (-42);
	shell->lexer = expand_lexer(shell, shell->lexer);
	if (!shell->lexer)
		return (-42);
	if (create_cmds(shell) == -42)
		return (-42);
	execute_pipeline(shell);
	if (g_last_signal)
		set_error_signal(shell);
	return (free_interactive(shell), 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		loop_value;

	if (argc != 1)
		return (printf("Usage: ./minishell\n"), argv++, 1);
	if (init_struct(&shell, envp) == -42)
		return (free_everything(&shell), 1);
	g_last_signal = 0;
	general_signals();
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
	return (free_everything(&shell), shell.exit_code);
}
