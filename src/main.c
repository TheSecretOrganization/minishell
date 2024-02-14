/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/02/14 12:34:16 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"

int	g_signal = 0;

static t_code	init_data(t_data *data, char **envp)
{
	char	*cwd;

	cpy_envp(data, envp);
	if (!data->envp)
		return (C_MEM);
	data->line = NULL;
	data->cmd = NULL;
	data->status = 0;
	data->path = NULL;
	if (get_path(data))
		return (ft_fsplit(data->envp), C_MEM);
	ft_getcwd(&cwd);
	if (cwd)
		if (ft_setenv(data, "PWD", cwd))
			return (free(cwd), ft_fsplit(data->envp), ft_fsplit(data->path),
				C_MEM);
	return (free(cwd), C_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	((void)argc, (void)argv, register_signals());
	if (init_data(&data, envp) != C_SUCCESS)
		return (1);
	while (prompt(&data))
	{
		if (g_signal == SIGINT)
			data.status = 130;
		g_signal = 0;
		data.line = ft_fstrtrim(data.line, " \t");
		if (!data.line)
			(clean_data(&data), exit(C_MEM));
		if (!*(data.line))
			continue ;
		data.status = parse_line(&data);
		if (data.status == C_BAD_USE)
			continue ;
		data.status = dispatch_cmd(&data) % 255;
		free_cmd(data.cmd);
	}
	return (ft_printf("exit\n"), ft_fsplit(data.path), ft_fsplit(data.envp),
		clear_history(), C_SUCCESS);
}
