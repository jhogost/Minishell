/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:37:34 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/14 16:34:46 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(int type, t_word *word)
{
	t_token	*tok;

	if (!word)
		return (NULL);
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	if (isbuiltin(word->str) == 0)
		tok->type = BUILTIN;
	else
		tok->type = type;
	tok->word = word;
	tok->next = NULL;
	tok->prev = NULL;
	return (tok);
}

void	add_token(t_token **lexer, t_token *new)
{
	t_token	*tmp;

	if (!*lexer)
	{
		*lexer = new;
		return ;
	}
	tmp = *lexer;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_token	*extract_operator(char *s, int *i)
{
	t_token	*tok;

	tok = handle_and(s, i);
	if (!tok)
		tok = handle_pipe_or(s, i);
	if (!tok)
		tok = handle_redir_in(s, i);
	if (!tok)
		tok = handle_redir_out(s, i);
	return (tok);
}

t_word	*extract_word(char *s, int *i)
{
	t_word	*word;

	word = init_word();
	if (!word)
		return (NULL);
	if (s[*i] == '\'')
		word->expand = 0;
	while (s[*i] && !is_space(s[*i]) && !is_operator(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			word->str = handle_quote(s, i, word->str);
			if (!word->str)
				return (NULL);
		}
		else
		{
			word->str = handle_plain_text(s, i, word->str);
			if (!word->str)
				return (NULL);
		}
	}
	return (word);
}

t_token	*build_lexer(char *input, t_token *lexer)
{
	t_token	*token;
	int		i;

	lexer = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (is_operator(input[i]))
		{
			token = extract_operator(input, &i);
			if (!token)
				return (NULL);
			add_token(&lexer, token);
		}
		else
		{
			token = new_token(WORD, extract_word(input, &i));
			if (!token)
				return (NULL);
			add_token(&lexer, token);
		}
	}
	return (lexer);
}
