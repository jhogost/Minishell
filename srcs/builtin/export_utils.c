/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:38:17 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/15 15:38:17 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_export_var(t_shell *shell, char *var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (shell->export[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	i = 0;
	while (shell->export[i])
	{
		new_envp[i] = shell->export[i];
		i++;
	}
	new_envp[i] = ft_strdup(var);
	new_envp[i + 1] = NULL;
	free(shell->export);
	shell->export = new_envp;
}

static void	update_shlvl(t_shell *shell)
{
	size_t	i;
	int		lvl;
	char	*num_ptr;
	char	*new_var;

	i = 0;
	while (shell->export[i])
	{
		if (ft_strncmp(shell->export[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(shell->export[i] + 6) + 1;
			num_ptr = ft_itoa(lvl);
			if (!num_ptr)
				return ;
			new_var = strjoin_free(ft_strdup("SHLVL="), num_ptr);
			if (!new_var)
				return ;
			free(shell->export[i]);
			shell->export[i] = new_var;
			return ;
		}
		i++;
	}
}

int	get_export(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->export = malloc(sizeof(char *) * (i + 1));
	if (!shell->export)
		return (-42);
	i = -1;
	while (envp[++i])
	{
		shell->export[i] = ft_strdup(envp[i]);
		if (!shell->export[i])
		{
			while (--i >= 0)
				free(shell->export[i]);
			free(shell->export);
			return (-42);
		}
	}
	shell->export[i] = NULL;
	update_shlvl(shell);
	return (0);
}

int	verify_export(char *s)
{
	int	i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (-1);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

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
