/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:54 by averin            #+#    #+#             */
/*   Updated: 2024/02/08 12:30:26 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
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

static void	handle_sigint(int signal)
{
	int	fd;

	(void)signal;
	fd = open("/dev/null", O_RDONLY);
	if (fd == -1)
		return ;
	if (dup2(fd, 0) == -1)
		return ;
	close(fd);
	ft_putstr_fd("\n", 1);
}

static void read_here_doc(t_exec *exec, char *delimiter, int wfd)
{
	char	*line;
	size_t	len;

	line = readline("here_doc > ");
	len = ft_strlen(delimiter);
	while (line && ft_strncmp(delimiter, line, len))
		(ft_putendl_fd(line, wfd), free(line), line = readline("here_doc > "));
	close(wfd);
	(clean_data(exec->data), ft_fsplit(exec->data->envp), ft_fsplit(exec->args),
		free(line), exit(C_SUCCESS));
}

static int	setup_here_doc(t_exec *exec)
{
	struct sigaction	saction;
	sigset_t			set;

	sigemptyset(&set);
	saction.sa_handler = handle_sigint;
	saction.sa_mask = set;
	saction.sa_flags = 0;
	if (sigaction(SIGINT, &saction, NULL) == -1)
		return (perror("sigaction"), C_GEN);
	if (exec->pipes[0] != -1)
		close(exec->pipes[0]);
	if (exec->pipes[1] != -1)
		close(exec->pipes[1]);
	clear_history();
	return (C_SUCCESS);
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
