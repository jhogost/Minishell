/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:45:47 by jbayet            #+#    #+#             */
/*   Updated: 2026/03/25 21:11:12 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	**tokens_to_argv(t_token **lexer)
{
	char	**argv;
	int		count;
	int		i;

	count = count_until_pipe(*lexer);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*lexer && (*lexer)->type != PIPE)
	{
		if ((*lexer)->type == WORD)
		{
			argv[i] = ft_strdup((*lexer)->word);
			if (!argv[i])
				return (free_argv(argv, i), NULL);
			i++;
		}
		*lexer = (*lexer)->next;
	}
	argv[i] = NULL;
	if (*lexer && (*lexer)->type == PIPE)
		*lexer = (*lexer)->next;
	return (argv);
}

int	create_cmds(t_shell *shell)
{

}
*/
