/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:37:34 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/19 10:09:29 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int whatisword(char *line)
{
    if (ft_strcmp(line, "|") == 0)
        return (PIPE);
    if (ft_strcmp(line, ">") == 0 || ft_strcmp(line, ">>") == 0 ||
        ft_strcmp(line, "<") == 0 || ft_strcmp(line, "<<") == 0)
        return (REDIRECTION);
    return (ARGUMENT);
}

t_shell	*ft_new_node(char *word)
{
	t_shell	*new;

	new = malloc(sizeof(t_shell));
	if (!new)
		return (NULL);
	new->word = strdup(word); 
	new->whatisit = whatisword(word);
	new->next = NULL;
	return (new);
}

void	ft_add_back(t_shell **lexer, t_shell *new)
{
	t_shell	*tmp;

	if (!*lexer)
	{
		*lexer = new;
		return ;
	}
	tmp = *lexer;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	**lexical(char *line, t_shell **lexer)
{
	char	**splitted;
	int		i;
	t_shell	*new_node;

	i = 0;
	splitted = ft_split(line, " ");
	if (!splitted)
		return (NULL);
	*lexer = NULL;
	while (splitted[i])
	{
		new_node = ft_new_node(splitted[i]);
		if (!new_node)
			return (NULL); 
		ft_add_back(lexer, new_node);
		i++;
	}
	return (splitted);
}
//TODO put the entire line in the lexer / structure
//0 operateur de controle -> || &&
//1 pipe -> |
//2 redirection -> > < >> <<
//3 argument/flag -> -la test.txt
//4 command/builtin -> ls echo cat exit pwd
//TODO after lexer, detect simple and double quotes ($ for double quotes)
//and detect them as one word