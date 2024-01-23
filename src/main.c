/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/01/23 11:40:37 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	char	**path;

	((void)argc, (void)argv);
	line = NULL;
	path = get_path();
	if (!path)
		return (C_GEN);
	register_signals();
	while (prompt(&line))
		dispatch_cmd(cmd, path, envp);
	free_cmd(cmd);
	ft_fsplit(path);
	return (0);
}
