/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:54 by averin            #+#    #+#             */
/*   Updated: 2024/02/08 10:06:17 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

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

static int	here_doc_prompt(char *delimiter, int wfd)
{
	(void)delimiter;
	(void)wfd;
}

int	here_doc(char *delimiter)
{
	int		wfd;
	int		rfd;
	char	*filename;

	filename = find_heredoc_file();
	if (!filename)
		return (-2);
	wfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (wfd == -1)
		return (free(filename), -1);
	rfd = open(filename, O_RDONLY);
	if (rfd == -1)
		return (free(filename), close(wfd), -1);
	unlink(filename);
	if (here_doc_prompt(delimiter, wfd) != C_SUCCESS)
		return (close(wfd), close(rfd), -2);
	return (close(wfd), rfd);
}
