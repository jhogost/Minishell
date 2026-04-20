/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:41:36 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/01 15:41:36 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_but_with_quotes(char **var)
{
	int	i;
	int	j;

	i = 0;
	while (var && var[i])
	{
		j = 0;
		write(1, "export ", 7);
		while (var[i][j] && var[i][j] != '=')
			write(1, &var[i][j++], 1);
		if (var[i][j] == '=')
		{
			write(1, "=\"", 2);
			j++;
			while (var[i][j])
				write(1, &var[i][j++], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}
// Print the env but with quotes around the value of each variable

int	get_env_index(char **envp, char *var)
{
	int	i;
	int	key_len;

	key_len = 0;
	while (var[key_len] && var[key_len] != '=')
		key_len++;
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], var, key_len) == 0
			&& (envp[i][key_len] == '=' || envp[i][key_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
//search if the variable already exists in envp

void	replace_env_var(t_shell *shell, char *var, int index, int whichone)
{
	if (whichone == 0)
	{
		free(shell->envp[index]);
		shell->envp[index] = ft_strdup(var);
	}
	if (whichone == 1)
	{
		free(shell->export[index]);
		shell->export[index] = ft_strdup(var);
	}
}
//free the old variable and replace it with the new one

void	add_env_var(t_shell *shell, char *var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (shell->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	i = 0;
	while (shell->envp[i])
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(var);
	new_envp[i + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
}
//add a new variable to envp

int	builtin_export(char **argv, t_shell *shell)
{
	int	i;
	int	idx_export;
	int	idx_env;

	i = 1;
	if (!argv[i])
		return (env_but_with_quotes(shell->export), 0);
	while (argv[i])
	{
		idx_export = get_env_index(shell->export, argv[i]);
		idx_env = get_env_index(shell->envp, argv[i]);
		if (idx_export >= 0)
			replace_env_var(shell, argv[i], idx_export, 1);
		else
			add_export_var(shell, argv[i]);
		if (ft_strchr(argv[i], '='))
		{
			if (idx_env >= 0)
				replace_env_var(shell, argv[i], idx_env, 0);
			else
				add_env_var(shell, argv[i]);
		}
		i++;
	}
	return (0);
}
