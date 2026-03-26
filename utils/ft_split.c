/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:13:35 by jbayet            #+#    #+#             */
/*   Updated: 2026/03/26 13:26:44 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char c, char *charset)
{
	int	i;

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
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_sep(str[i], charset))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && !is_sep(str[i], charset))
				i++;
		}
	}
	return (count);
}

char	*copy(char *word, char *charset)
{
	int		count;
	int		i;
	char	*copy_word;

	count = 0;
	i = 0;
	while (word[count] && !is_sep(word[count], charset))
		count++;
	copy_word = malloc((count + 1) * sizeof(char));
	if (!copy_word)
		return (NULL);
	while (i < count)
	{
		copy_word[i] = word[i];
		i++;
	}
	copy_word[i] = '\0';
	return (copy_word);
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	int		j;
	char	**result;

	result = malloc((word_count(str, charset) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && is_sep(str[i], charset))
			i++;
		if (str[i])
		{
			result[j] = copy(&str[i], charset);
			j++;
			while (str[i] && !is_sep(str[i], charset))
				i++;
		}
	}
	result[j] = NULL;
	return (result);
}

/*
int	main(int argc, char **argv)
{
	int	i = 0;
	if (argc != 3)
	{
		printf("Error argument");
		return (1);
	}
	char	**result = ft_split(argv[1], argv[2]);
	while (result[i])
	{
		printf("%d : %s\n", i, result[i]);
		i++;
	}
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/
