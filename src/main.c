/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/01/23 12:35:27 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	char	**path;
	int		status;

	((void)argc, (void)argv);
	line = NULL;
	cmd = NULL;
	status = 0;
	path = get_path();
	if (!path)
		return (C_GEN);
	register_signals();
	while (prompt(&line, status))
	{
		status = parse_line(&cmd, line);
		if (status == C_BAD_USE)
			continue ;
		status = dispatch_cmd(cmd, path, envp);
	}
	(free_cmd(cmd), ft_fsplit(path));
	return (C_SUCCESS);
}
