/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:19:34 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/20 11:19:20 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_closed(char *s)
{
	int		i;
	char	quote;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			count++;
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				count++;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (count % 2 == 0);
}

int	verify_line(char *line, t_shell *shell)
{
	if (!line)
		return (-1);
	if (count_tokens(line) == -42)
		return (printf("Syntax error: too many operators\n"),
			shell->exit_code = 2, -42);
	if (count_heredoc(line) > 16)
	{
		printf("maximum here-document count exceeded\n");
		free_interactive(shell);
		exit(2);
	}
	if (line[0] == '|' || line[0] == '&')
		return (printf("Syntax error: unexpected token `%c'\n", line[0]),
			shell->exit_code = 2, -42);
	if (quote_closed(line) == 0)
		return (printf("Syntax error: unclosed quote\n"),
			shell->exit_code = 2, -42);
	if (wrong_last_token(line))
		return (printf("syntax error near unexpected token `newline'\n"),
			shell->exit_code = 2, -42);
	return (0);
}

int	loop_count_tokens(char *word, int *i, int *count, char *operator)
{
	*count = 0;
	if (word[*i] == '\'' || word[*i] == '"')
	{
		*operator = word[*i];
		*i += 1;
		while (word[*i] && word[*i] != *operator)
			*i += 1;
	}
	else if (is_operator(word[*i]))
	{
		*operator = word[*i];
		*count += 1;
		while (is_operator(word[*i]) && word[*i] == *operator)
		{
			*count += 1;
			*i += 1;
		}
		if (*count > 3)
			return (-42);
	}
	else
		*i += 1;
	return (0);
}

int	count_tokens(char *word)
{
	int		i;
	int		count;
	char	operator;

	i = 0;
	count = 0;
	while (word[i])
	{
		if (loop_count_tokens(word, &i, &count, &operator) == -42)
			return (-42);
	}
	return (0);
}

int	count_heredoc(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1])
		{
			if (line[i + 1] == '<')
			{
				count++;
				i++;
			}
		}
		i++;
	}
	return (count);
}
