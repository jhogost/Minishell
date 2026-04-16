/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:33:06 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/16 19:51:28 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc(char *line, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
			line = expand_token(shell, line, i);
		i++;
	}
	return (line);
}

char	*read_heredoc(t_redir *redir, t_shell *shell)
{
	char	*content;
	char	*line;

	content = NULL;
	content = ft_strdup("");
	g_last_signal = 0;
	heredoc_signals();
	while (!g_last_signal)
	{
		line = readline("> ");
		if (!line)
			break ;
		shell->count_line++;
		if (ft_strcmp(line, redir->file) == 0)
			return (general_signals(), free(line), content);
		if (need_expand(line, redir->expand))
			line = expand_heredoc(line, shell);
		content = strjoin_free(content, line);
		content = strjoin_free(content, ft_strdup("\n"));
		//printf("bash: warning: here-document at line ");
		//printf("%d delimited by end-of-file (wanted `%s')", count, redir->file);
	}
	return (general_signals(), content);
}
