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

void	free_everything(t_shell *shell, char *line, t_token **lexer)
{
	free_things();
	free_line(line, lexer);
	free_env(shell);
}

void	free_env(t_shell *shell)
{
	int	i;

	if (shell->envp)
	{
		i = 0;
		while (shell->envp[i])
		{
			free(shell->envp[i]);
			i++;
		}
		free(shell->envp);
		shell->envp = NULL;
	}
}

void	free_line(char *line, t_token **lexer)
{
	t_token	*tmp;
	t_token	*next;

	if (line)
		free(line);
	if (lexer && *lexer)
	{
		tmp = *lexer;
		while (tmp)
		{
			next = tmp->next;
			free(tmp->word);
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
