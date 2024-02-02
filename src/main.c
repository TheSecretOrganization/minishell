/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/02/02 16:05:24 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	g_signal = 0;

void	init_data(t_data *data, char **envp)
{
	cpy_envp(data, envp);
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
		g_signal = 0;
		data.line = ft_fstrtrim(data.line, " ");
		if (!data.line)
			(clean_data(&data), exit(C_MEM));
		if (!*(data.line))
		{
			data.status = 0;
			continue ;
		}
		data.status = parse_line(&data);
		if (data.status == C_BAD_USE)
			continue ;
		data.status = dispatch_cmd(data.cmd, data.path, data.envp);
		free_cmd(data.cmd);
	}
	return (ft_printf("exit\n"), ft_fsplit(data.path), ft_fsplit(data.envp),
		C_SUCCESS);
}
