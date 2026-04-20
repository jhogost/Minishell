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

void	check_loop(char **av, t_shell *shell, int i, int *err)
{
	int	ex;
	int	en;

	if (verify_export(av[i]) == -1)
	{
		ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
		*err = 1;
		return ;
	}
	ex = get_env_index(shell->export, av[i]);
	en = get_env_index(shell->envp, av[i]);
	if (ex >= 0)
		replace_env_var(shell, av[i], ex, 1);
	else
		add_export_var(shell, av[i]);
	if (ft_strchr(av[i], '='))
	{
		if (en >= 0)
			replace_env_var(shell, av[i], en, 0);
		else
			add_env_var(shell, av[i]);
	}
	return ;
}

int	builtin_export(char **av, t_shell *shell)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	if (!av[1])
		return (env_but_with_quotes(shell->export), 0);
	while (av[++i])
		check_loop(av, shell, i, &err);
	return (err);
}
