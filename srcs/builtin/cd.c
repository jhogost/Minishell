/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:39:33 by hhervieu          #+#    #+#             */
/*   Updated: 2026/04/01 15:39:33 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_cd(void)
{
	ft_putstr_fd("chdir: error retrieving current directory", 2);
	ft_putstr_fd(": getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}

char	*ft_getenv(char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static void	set_env_var(t_shell *shell, char *key, char *value)
{
	char	*new;
	int		idx;

	if (!value)
		return ;
	new = ft_strjoin(key, value);
	if (!new)
		return ;
	idx = get_env_index(shell->envp, key);
	if (idx >= 0)
	{
		replace_env_var(shell, new, idx, 0);
		replace_env_var(shell, new, idx, 1);
	}
	else
	{
		add_export_var(shell, new);
		add_env_var(shell, new);
	}
	free(new);
}

void	update_envp(t_shell *shell)
{
	char	cwd[1024];
	char	*old;

	old = ft_getenv("PWD", shell->envp);
	if (old)
		old = ft_strdup(old);
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (ft_getenv("PWD", shell->envp) == NULL)
			set_env_var(shell, "OLDPWD=", "");
		else
		{
			if (old)
				set_env_var(shell, "OLDPWD=", old);
			set_env_var(shell, "PWD=", cwd);
		}
	}
	else
	{
		print_error_cd();
		if (old)
			set_env_var(shell, "OLDPWD=", old);
	}
	free(old);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*path;
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL && argv[1]
		&& ft_strcmp(argv[1], "..") == 0)
		return (print_error_cd(), 1);
	if (!argv[1])
	{
		path = ft_getenv("HOME", shell->envp);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	else
		path = argv[1];
	if (chdir(path) != 0)
		return (perror("minishell: cd"), 1);
	update_envp(shell);
	return (0);
}
