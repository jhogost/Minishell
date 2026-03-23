/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:37:34 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/23 16:37:52 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	whatisword(char *word, t_token *prev)
{
	if (!word)
		return (-1);
	if (ft_strcmp(word, "&&") == 0 || (ft_strcmp(word, "||") == 0
			&& ft_countchar(word, '|') == 2))
		return (CONTROL);
	if (ft_strcmp(word, "|") == 0 && ft_countchar(word, '|') == 1)
		return (PIPE);
	if (ft_strcmp(word, ">") == 0 || ft_strcmp(word, ">>") == 0
		|| ft_strcmp(word, "<") == 0 || ft_strcmp(word, "<<") == 0)
		return (REDIRECTION);
	if (!prev)
		return (COMMAND);
	else if (prev->type == PIPE || prev->type == CONTROL)
		return (COMMAND);
	return (ARGUMENT);
}
*/

t_token	*new_token(int type, char *word)
{
	t_token	*tok;

	if (!word)
		return (NULL);
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
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

char	*extract_word(char *s, int *i)
{
	char	*res;

	res = NULL;
	while (s[*i] && !is_space(s[*i]) && !is_operator(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			res = handle_quote(s, i, res);
			if (!res)
				return (NULL);
		}
		else
		{
			res = handle_plain_text(s, i, res);
			if (!res)
				return (NULL);
		}
	}
	return (res);
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

// TODO put the entire line in the lexer / structure
// 0 operateur de controle -> || &&  !!! PAS BESOIN DE LE GERER A PRIORI !!!
// 1 pipe -> |
// 2 redirection -> > < >> <<
// 3 argument/flag -> -la test.txt
// 4 command/builtin -> ls echo cat exit pwd
// TODO after lexer, detect simple and double quotes ($ for double quotes)
// and detect them as one word
