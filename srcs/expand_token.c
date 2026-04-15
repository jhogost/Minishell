/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:58:56 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/15 16:29:47 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *str, int i, int *end)
{
	int	start;

	start = i + 1;
	if (str[start] == '?')
	{
		*end = start + 1;
		return (ft_strdup("?"));
	}
	*end = start;
	while (str[*end] && (ft_isalnum(str[*end]) || str[*end] == '_'))
		(*end)++;
	return (ft_substr(str, start, *end - start));
}

char	*get_env_value(char **envp, char *key)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*build_expanded(char *str, int i, int end, char *value)
{
	char	*before;
	char	*after;
	char	*res;

	before = ft_substr(str, 0, i);
	after = ft_strdup(str + end);
	res = strjoin_free(before, ft_strdup(value));
	res = strjoin_free(res, after);
	free(str);
	return (res);
}

char	*get_value(t_shell *shell, char *key)
{
	char	*tmp;
	char	*value;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(shell->exit_code));
	tmp = get_env_value(shell->envp, key);
	if (tmp)
		value = ft_strdup(tmp);
	else
		value = ft_strdup("");
	if (!value)
		return (NULL);
	return (value);
}

char	*expand_token(t_shell *shell, char *str, int i)
{
	int		end;
	char	*key;
	char	*value;
	char	*res;

	key = extract_key(str, i, &end);
	if (!key)
		return (str);
	value = get_value(shell, key);
	if (!value)
		return (free(key), str);
	res = build_expanded(str, i, end, value);
	free(key);
	free(value);
	return (res);
}
