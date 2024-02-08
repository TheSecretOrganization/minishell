/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:54 by averin            #+#    #+#             */
/*   Updated: 2024/02/08 13:20:36 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <errno.h>

static void read_here_doc(t_exec *exec, char *delimiter, int wfd)
{
	char	*line;
	size_t	len;
	int		db;

	db = delimiter[0] == '"';
	if (db)
	[
		delimiter = ft_strtrim(delimiter, "\"");
		if (!delimiter)
			return ;
	]
	line = readline("here_doc > ");
	len = ft_strlen(delimiter);
	while (line && ft_strncmp(delimiter, line, len))
		(ft_putendl_fd(line, wfd), free(line), line = readline("here_doc > "));
	close(wfd);
	(clean_data(exec->data), ft_fsplit(exec->data->envp), ft_fsplit(exec->args),
		free(line), exit(C_SUCCESS));
}

static int	here_doc_prompt(t_exec *exec, char *delimiter, int wfd, int rfd)
{
	pid_t	pid;
	int		code;

	pid = fork();
	code = C_SUCCESS;
	if (pid == -1)
		return (C_GEN);
	if (pid == 0)
	{
		close(rfd);
		if (setup_here_doc(exec))
			exit(C_GEN);
		read_here_doc(exec, delimiter, wfd);
	}
	else
		wait(&code);
	if (code == 1)
		return (-2);
	return (C_SUCCESS);
}

int	here_doc(t_exec *exec, char *delimiter)
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
	(unlink(filename), free(filename));
	if (here_doc_prompt(exec, delimiter, wfd, rfd) != C_SUCCESS)
		return (close(wfd), close(rfd), -2);
	return (close(wfd), rfd);
}
