/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:34:45 by averin            #+#    #+#             */
/*   Updated: 2024/01/10 13:49:42 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_singint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * Bind a signal to an handler
 * @param signal signal to bind
 * @param handler handler to call
*/
static void	register_action(int signal, void (*handler)(int))
{
	struct sigaction	saction;

	saction.sa_handler = handler;
	if (sigaction(signal, &saction, NULL) == -1)
		(perror("sigaction"), exit(EXIT_FAILURE));
}

/**
 * Bind signals to their handlers
*/
void	register_signals()
{
	register_action(SIGINT, &handle_singint);
	register_action(SIGQUIT, SIG_IGN);
}