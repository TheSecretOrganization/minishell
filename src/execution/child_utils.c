/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:12:45 by averin            #+#    #+#             */
/*   Updated: 2024/02/14 13:14:58 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	handle_sigint(int signal)
{
	g_signal = signal;
	printf("\n");
}

/**
 * Wait for all children
 * @param pid last execution pid
 * @return last execution exit code
*/
int	wait_children(int pid)
{
	int					wstatus;
	int					code;
	struct sigaction	old;

	code = C_SUCCESS;
	register_action(SIGINT, &old, &handle_sigint);
	while (errno != ECHILD)
	{
		if (wait(&wstatus) == pid)
		{
			if (WIFEXITED(wstatus))
				code = WEXITSTATUS(wstatus);
			else
				code = 128 + WTERMSIG(wstatus);
			if (WIFSIGNALED(code) && WTERMSIG(code) == SIGQUIT)
				printf("Quit\n");
		}
	}
	sigaction(SIGINT, &old, NULL);
	return (code);
}
