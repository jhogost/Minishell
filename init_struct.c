/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:41:04 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/23 10:41:04 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_struct(t_shell *shell, char **envp)
{
	shell->input = NULL;
	shell->exit_code = 0;
	if (get_env(envp, shell) == -42)
		return (-42);
	shell->path = getenv("PATH");
	if (!shell->path)
		shell->path = NULL;
	return (0);
}
