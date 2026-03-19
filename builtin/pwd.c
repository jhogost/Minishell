/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhervieu <hhervieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:36:04 by hhervieu          #+#    #+#             */
/*   Updated: 2026/03/11 13:36:04 by hhervieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	str[PATH_MAX];

	if (getcwd(str, sizeof(str)) == NULL)
		return (-42);
	printf("%s\n", str);
	return (0);
}
