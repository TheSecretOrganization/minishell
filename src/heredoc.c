/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:54 by averin            #+#    #+#             */
/*   Updated: 2024/02/08 09:36:50 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Find a filename for here_doc
 *
 * @return char* file name or NULL
 */
static char	*find_heredoc_file(void)
{
	char	*file;
	int		size;

	size = 2;
	file = NULL;
	file = ft_calloc(size, sizeof(char));
	if (!file)
		return (NULL);
	ft_memset(file, 'a', size - 1);
	while (access(file, F_OK) != 0 && errno != ENOENT)
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

static void	here_doc_prompt(char *delimiter, int wfd)
{
	(void)delimiter;
	(void)wfd;
}

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
	while (ft_printf("here_doc > ") && oget_next_line(0, &line)
		&& g_signal == 0)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		(ft_putstr_fd(line, wfd), free(line));
	}
	if (g_signal == SIGINT)
		return (-2);
	if (line == NULL)
		ft_putstr_fd("\n", 1);
	close(wfd);
	return (rfd);
}
