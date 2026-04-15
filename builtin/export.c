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
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, key_len) == 0
			&& envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
//search if the variable already exists in envp

void	replace_env_var(t_shell *shell, char *var, int index)
{
	free(shell->envp[index]);
	shell->envp[index] = ft_strdup(var);
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
	int	index;

	i = 1;
	if (!argv[i])
		return (env_but_with_quotes(shell->envp), 0);
	while (argv[i])
	{
		if (verify_export(argv[i]) == 1)
		{
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
			return (1);
		}
		index = get_env_index(shell->envp, argv[i]);
		if (index >= 0)
			replace_env_var(shell, argv[i], index);
		else
			add_env_var(shell, argv[i]);
		i++;
	}
	return (0);
}
