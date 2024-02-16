/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:13:45 by averin            #+#    #+#             */
/*   Updated: 2024/02/15 22:59:55 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * @brief Find a filename for here_doc
 *
 * @return char* file name or NULL
 */
char	*find_heredoc_file(void)
{
	char	*file;
	int		size;

	size = 2;
	file = NULL;
	file = ft_calloc(size, sizeof(char));
	if (!file)
		return (NULL);
	ft_memset(file, 'a', size - 1);
	while (access(file, F_OK) == 0)
	{
		free(file);
		if (++size < 0)
			return (NULL);
		file = ft_calloc(size, sizeof(char));
		if (!file)
			return (NULL);
		ft_memset(file, 'a', size - 1);
	}
	return (file);
}

static void	handle_sigint(int signal)
{
	int	fd;

	g_signal = signal;
	fd = open("/dev/null", O_RDONLY);
	if (fd == -1)
		return ;
	if (dup2(fd, 0) == -1)
		return ;
	close(fd);
	ft_putstr_fd("\n", 1);
}

int	setup_here_doc(t_exec *exec)
{
	if (exec->pipes[0] != -1)
		close(exec->pipes[0]);
	if (exec->pipes[1] != -1)
		close(exec->pipes[1]);
	if (register_action(SIGINT, NULL, &handle_sigint))
		return (C_GEN);
	clear_history();
	return (C_SUCCESS);
}
