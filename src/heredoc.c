/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:54 by averin            #+#    #+#             */
/*   Updated: 2024/01/24 13:47:32 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *delimiter)
{
	int		wfd;
	int		rfd;
	char	*line;

	delimiter = ft_strjoin(delimiter, "\n");
	if (!delimiter)
		return (-1);
	wfd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	rfd = open("here_doc", O_RDONLY);
	unlink("here_doc");
	while (printf("heredoc > ") && oget_next_line(0, &line)
		&& g_signal != SIGINT)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		(ft_putstr_fd(line, wfd), free(line));
	}
	close(wfd);
	return (rfd);
}
