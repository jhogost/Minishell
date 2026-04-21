/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayet <jbayet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 00:25:06 by jbayet            #+#    #+#             */
/*   Updated: 2026/04/21 14:19:06 by jbayet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_signals(void)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigint);
}

void	general_signals(void)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
	signal(SIGINT, handler_ignor);
	signal(SIGQUIT, handler_ignor);
}

void	ignore_signals_heredoc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signals(void)
{
	signal(SIGINT, handler_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
