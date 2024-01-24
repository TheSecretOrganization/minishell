/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/01/24 14:59:26 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

void	init_data(t_data *data, char **envp)
{
	data->envp = envp;
	data->line = NULL;
	data->cmd = NULL;
	data->status = 0;
	data->path = get_path();
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	((void)argc, (void)argv);
	(init_data(&data, envp), register_signals());
	while (prompt(&data))
	{
		data.status = 0;
		if (!*(data.line))
			continue ;
		data.status = parse_line(&data);
		if (data.status == C_BAD_USE)
			continue ;
		data.status = dispatch_cmd(data.cmd, data.path, data.envp);
		free_cmd(data.cmd);
	}
	return (ft_fsplit(data.path), C_SUCCESS);
}
