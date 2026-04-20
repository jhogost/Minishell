/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:25:01 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/20 18:47:59 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

void	handler_sigint(int sig)
{
	(void)sig;
	g_last_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_ignor(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handler_heredoc_sigint(int sig)
{
	(void)sig;
	g_last_signal = 130;
}
