/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:41:01 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/24 15:45:52 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = strjoin_free(ft_strdup(dir), ft_strdup("/"));
	if (!tmp)
		return (NULL);
	full = strjoin_free(tmp, ft_strdup(cmd));
	return (full);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*full;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (paths && paths[i])
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	**get_path(t_shell *shell)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	if (shell->paths)
		free_paths(shell);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(shell->envp[i] + 5, ":");
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (path);
}
