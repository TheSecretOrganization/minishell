/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:44:54 by averin            #+#    #+#             */
/*   Updated: 2024/02/13 11:07:42 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"
#include <errno.h>

/**
 * @brief Expand vairables in line
 *
 * @param line pointer on the line red
 * @param status status of the last command
 * @return int
 */
static int	expand_hd(char **line, int status, char **envp)
{
	size_t	i;
	t_data	tmp;

	i = -1;
	tmp.line = *line;
	tmp.status = status;
	tmp.envp = envp;
	while ((*line)[++i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] && !ft_is_space((*line)[i + 1]))
		{
			if ((*line)[i + 1] == '?')
				(*line) = expand_status(&tmp);
			else
				(*line) = expand_variable(&tmp, &i);
			if (!(*line))
				return (C_MEM);
		}
	}
	return (C_SUCCESS);
}

/**
 * @brief Free all the data of the child
 *
 * @param exec exec data
 * @param delimiter delimiter of the here_doc
 * @param line line red
 * @param wfd unlinf file's fd
 */
static void	free_here_doc(t_exec *exec, char *delimiter, char *line, int wfd)
{
	(free(delimiter), delimiter = NULL);
	(free(line), line = NULL);
	(close(wfd), wfd = -1);
	clean_data(exec->data);
	ft_fsplit(exec->data->envp);
	ft_fsplit(exec->args);
}

/**
 * @brief Read user's input
 *
 * @param exec exec data
 * @param delimiter delimiter of the here_doc
 * @param wfd unlinf file's fd
 */
static void	read_here_doc(t_exec *exec, char *delimiter, int wfd)
{
	char	*line;
	size_t	len;
	int		db;
	int		expand;

	db = (delimiter[0] == '"' || delimiter[0] == '\'');
	expand = 1;
	if (db)
	{
		line = (char [2]){delimiter[0], 0};
		delimiter = ft_fstrtrim(delimiter, line);
		line = NULL;
		expand = 0;
		if (!delimiter)
			(free_here_doc(exec, delimiter, line, wfd), exit(C_MEM));
	}
	line = readline("here_doc > ");
	len = ft_strlen(delimiter) + 1;
	while (line && ft_strncmp(delimiter, line, len))
	{
		if (expand && expand_hd(&line, exec->data->status, exec->data->envp))
			(free_here_doc(exec, delimiter, line, wfd), exit(C_MEM));
		(ft_putendl_fd(line, wfd), free(line), line = readline("here_doc > "));
	}
	(free_here_doc(exec, delimiter, line, wfd), exit(g_signal));
}

/**
 * @brief Create the here_doc child
 *
 * @param exec exec data
 * @param delimiter delimiter of the here_doc
 * @param wfd unlinf file's fd
 * @param rfd new infile fd
 * @return int
 */
static int	here_doc_prompt(t_exec *exec, char *delimiter, int wfd, int rfd)
{
	pid_t	pid;
	int		code;
	char	*cpy;

	pid = fork();
	code = C_SUCCESS;
	if (pid == -1)
		return (C_GEN);
	if (pid == 0)
	{
		close(rfd);
		if (setup_here_doc(exec))
			(free_here_doc(exec, NULL, NULL, wfd), exit(C_GEN));
		cpy = ft_strdup(delimiter);
		if (!cpy)
			(free_here_doc(exec, NULL, NULL, wfd), exit(C_MEM));
		read_here_doc(exec, cpy, wfd);
	}
	(close(wfd), register_action(SIGINT, NULL, SIG_IGN));
	if (wait(&code) == -1)
		return (perror("wait"), C_GEN);
	register_signals();
	if (WIFEXITED(code) && WEXITSTATUS(code) == SIGINT)
		return (-2);
	return (C_SUCCESS);
}

/**
 * @brief Reproduce the here_doc behaviour of bash
 *
 * @param exec exec data
 * @param delimiter delimiter of the here_doc
 * @return int fd of the new infile or an error
 */
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
		return (close(rfd), -2);
	return (rfd);
}
