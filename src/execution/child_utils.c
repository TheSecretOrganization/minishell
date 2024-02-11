/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:12:45 by averin            #+#    #+#             */
/*   Updated: 2024/02/11 16:20:12 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * Wait for all children
 * @param pid last execution pid
 * @return last execution exit code
*/
int	wait_children(int pid)
{
	int	wstatus;
	int	code;

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
	return (code);
}
