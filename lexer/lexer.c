/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:37:34 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/19 15:05:05 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	whatisword(char *line)
{
	if (!line)
		return (-1);
	if (ft_strcmp(line, "&&") == 0 || ft_strcmp(line, "||") == 0)
		return (CONTROL);
	if (ft_strcmp(line, "|") == 0)
		return (PIPE);
	if (ft_strcmp(line, ">") == 0 || ft_strcmp(line, ">>") == 0
		|| ft_strcmp(line, "<") == 0 || ft_strcmp(line, "<<") == 0)
		return (REDIRECTION);
	return (COMMAND);
}

t_shell	*ft_new_node(char *word, char *whole_line)
{
	t_shell	*new;

	new = malloc(sizeof(t_shell));
	if (!new)
		return (NULL);
	new->word = ft_strdup(word);
	if (!new->word)
		return (free(new), NULL);
	new->whatisit = whatisword(word);
	if (new->whatisit == -1)
		return (free(new), NULL);
	new->whole_line = ft_strdup(whole_line);
	if (!new->whole_line)
		return (free(new->word), free(new), NULL);
	new->prev = NULL;
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
	new->prev = tmp;
}

int	lexical(char *line, t_shell **lexer)
{
	char	**splitted;
	int		i;
	t_shell	*new_node;
	char	*temp;

	i = 0;
	temp = line;
	splitted = ft_split(line, " ");
	if (!splitted)
		return (-42);
	while (splitted[i])
	{
		new_node = ft_new_node(splitted[i], temp);
		if (!new_node)
			return (-42);
		ft_add_back(lexer, new_node);
		i++;
	}
	free_splitted(splitted);
	return (0);
}
// TODO put the entire line in the lexer / structure
// 0 operateur de controle -> || &&
// 1 pipe -> |
// 2 redirection -> > < >> <<
// 3 argument/flag -> -la test.txt
// 4 command/builtin -> ls echo cat exit pwd
// TODO after lexer, detect simple and double quotes ($ for double quotes)
// and detect them as one word