/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:10:49 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/15 14:52:15 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_token(t_token *tok, t_token **new_lexer)
{
	char	**words;
	int		i;
	t_token	*new;
	t_word	*w;

	words = ft_split(tok->word->str, " \t\n\r\v\f");
	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		w = malloc(sizeof(t_word));
		if (!w)
			return ;
		w->str = ft_strdup(words[i]);
		w->expand = 0;
		new = new_token(WORD, w);
		add_token(new_lexer, new);
		i++;
	}
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

int	need_expand(char *str, int expand)
{
	int	i;

	i = 0;
	if (!expand)
		return (0);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (ft_isalnum(str[i + 1]) || str[i + 1] == '?')
				return (1);
		}
		i++;
	}
	return (0);
}

void	process_token(t_shell *shell, t_token *tmp, t_token **new_lexer)
{
	int	i;

	if (need_expand(tmp->word->str, tmp->word->expand))
	{
		i = 0;
		while (tmp->word->str[i])
		{
			if (tmp->word->str[i] == '$' && tmp->word->str[i + 1]
				&& (ft_isalnum(tmp->word->str[i + 1])
					|| tmp->word->str[i + 1] == '?'))
				tmp->word->str = expand_token(shell, tmp->word->str, i);
			i++;
		}
		if (i_white_char_str(tmp->word->str) != -1)
		{
			split_token(tmp, new_lexer);
			free(tmp->word->str);
			free(tmp->word);
			free(tmp);
		}
		else
			add_token(new_lexer, tmp);
	}
	else
		add_token(new_lexer, tmp);
}

t_token	*expand_lexer(t_shell *shell, t_token *lexer)
{
	t_token	*tmp;
	t_token	*next;
	t_token	*new_lexer;

	new_lexer = NULL;
	tmp = lexer;
	while (tmp)
	{
		next = tmp->next;
		tmp->next = NULL;
		tmp->prev = NULL;
		process_token(shell, tmp, &new_lexer);
		tmp = next;
	}
	return (new_lexer);
}
