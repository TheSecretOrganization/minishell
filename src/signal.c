/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:34:45 by averin            #+#    #+#             */
/*   Updated: 2024/02/11 15:19:23 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_singint(int signal)
{
	g_signal = signal;
}

/**
 * Bind a signal to an handler
 * @param signal signal to bind
 * @param handler handler to call
*/
int	register_action(int signal, struct sigaction *old, void (*handler)(int))
{
	struct sigaction	saction;
	sigset_t			set;

	sigemptyset(&set);
	saction.sa_handler = handler;
	saction.sa_mask = set;
	saction.sa_flags = 0;
	if (sigaction(signal, &saction, old) == -1)
		return (perror("sigaction"), C_GEN);
	return (C_SUCCESS);
}

/**
 * Bind signals to their handlers
*/
void	register_signals(void)
{
	register_action(SIGINT, NULL, &handle_singint);
	register_action(SIGQUIT, NULL, SIG_IGN);
}
