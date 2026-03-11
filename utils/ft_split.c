/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:21:56 by jbayet            #+#    #+#             */
/*   Updated: 2026/03/11 12:58:03 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*strdup_until_sep(char *word, char *charset)
{
	int		i;
	char	*copy;

	i = 0;
	while (word[i] && !is_sep(word[i], charset))
		i++;
	copy = malloc(sizeof(char) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (word[i] && !is_sep(word[i], charset))
	{
		copy[i] = word[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	word_count(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
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

char	**ft_split(char *str, char *charset)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr = malloc(sizeof(char *) * (word_count(str, charset) + 1));
	if (!arr)
		return (NULL);
	while (str[i])
	{
		while (str[i] && is_sep(str[i], charset))
			i++;
		if (str[i])
		{
			arr[j] = strdup_until_sep(&str[i], charset);
			j++;
			while (str[i] && !is_sep(str[i], charset))
				i++;
		}
	}
	free(str);
	arr[j] = (NULL);
	return (arr);
}
/*
int	main(int argc, char **argv)
{
	char	**arr;
	int	i;

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
