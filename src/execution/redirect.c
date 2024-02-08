/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:46:32 by averin            #+#    #+#             */
/*   Updated: 2024/02/08 12:17:33 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * @brief Open a single infile and set his fd
 * Close the current fd if one is already open
 *
 * @param element t_infile * info
 * @param exec current exec
 * @return int if file has been opened
 */
static int	open_infile(void *element, t_exec *exec)
{
	t_infile	*el;

	el = (t_infile *)element;
	if (exec->infile != -1)
		(close(exec->infile), exec->infile = -1);
	if (el->intype == IT_INFILE)
		exec->infile = open(el->filename, O_RDONLY);
	else if (el->intype == IT_HERE_DOC)
		exec->infile = here_doc(exec, el->filename);
	else if (el->intype == IT_CREATE)
		exec->infile = open(el->filename, O_CREAT | O_RDONLY, 0644);
	if (exec->infile == -1)
		perror(el->filename);
	return (exec->infile != -1);
}

/**
 * Open or create infile and set corresponding fd in exec
 * @param cmd Command in wich search infile
 * @param exec Where to store infile fd
 * @return `C_SUCCESS` or `C_GEN` when error
*/
int	init_infile(t_cmd cmd, t_exec *exec)
{
	if (for_elements(cmd, T_INFILE, exec, &open_infile) != C_SUCCESS)
	{
		if (exec->infile == -2)
			return (C_BAD_USE);
		return (C_GEN);
	}
	return (C_SUCCESS);
}

/**
 * @brief Open a single outfile and set his fd
 * Close the current fd if one is already open
 *
 * @param element t_outfile * info
 * @param exec current exec
 * @return int if file has been opened
 */
static int	open_outfile(void *element, t_exec *exec)
{
	t_outfile	*el;

	el = (t_outfile *)element;
	if (exec->outfile != -1)
		(close(exec->outfile), exec->outfile = -1);
	if (el->outtype == OT_TRUNCATE)
		exec->outfile = open(el->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (el->outtype == OT_APPEND)
		exec->outfile = open(el->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (exec->outfile == -1)
		perror(el->filename);
	return (exec->outfile != -1);
}

/**
 * Open outfiles and set corresponding fd in exec
 * @param cmd Command in wich search infile
 * @param exec Where to store infile fd
 * @return `C_SUCCESS` or `C_GEN` when error
*/
int	init_outfile(t_cmd cmd, t_exec *exec)
{
	if (for_elements(cmd, T_OUTFILE, exec, &open_outfile) != C_SUCCESS)
		return (C_GEN);
	return (C_SUCCESS);
}

/**
 * If the command have a pipe create it and store it in exec and close if
 * another pipe is already open
 * @param cmd Where search for pipe
 * @param exec Where store thie pipe
 * @return `C_SUCCESS` or `C_GEN` when error
*/
int	init_pipe(t_cmd *cmd, t_exec *exec)
{
	if (find_element(*cmd, T_PIPE))
	{
		if (pipe(exec->pipes) == -1)
			return (perror("pipe"), C_GEN);
		exec->outfile = exec->pipes[1];
	}
	return (C_SUCCESS);
}
