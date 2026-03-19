/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:21:56 by jbayet            #+#    #+#             */
/*   Updated: 2026/03/19 19:11:51 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_quote(char c, char *quote)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

int	is_sep(char c, char *charset, char quote)
{
	int	i;

	if (quote)
		return (0);
	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	word_count(char *str, char *charset)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && is_sep(str[i], charset, quote))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && !is_sep(str[i], charset, quote))
			{
				update_quote(str[i], &quote);
				i++;
			}
		}
	}
	return (count);
}

char	*dup_word(char *str, int *begin_word, char *charset)
{
	char	*word;
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (is_sep(str[i], charset, quote))
			break ;
		update_quote(str[i++], &quote);
	}
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && !is_sep(str[i], charset, quote))
	{
		update_quote(str[i], &quote);
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	*begin_word += i;
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	char	**arr;
	int		i;
	int		j;

	arr = malloc(sizeof(char *) * (word_count(str, charset) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && is_sep(str[i], charset, 0))
			i++;
		if (str[i])
		{
			arr[j] = dup_word(&str[i], &i, charset);
			j++;
		}
	}
	arr[j] = NULL;
	return (arr);
}

/*
int	main(int argc, char **argv)
{
	char	**arr;
	int		i;

	if (argc != 3)
	{
		printf("error argument");
		return (1);
	}
	arr = ft_split(argv[1], argv[2]);
	i = 0;
	while (arr[i])
	{
		printf("%d: %s\n", i, arr[i]);
		i++;
	}
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
*/
