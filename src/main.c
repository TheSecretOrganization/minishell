/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/01/17 15:12:33 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	main(void)
{
	char	*line;
	t_cmd	*cmd;

	line = NULL;
	cmd = NULL;
	register_signals();
	// line = ft_strdup("echo \"$PATH test || \" &| rev ");
	// if (!line)
	// 	return (C_MEM);
	// (parse_line(&cmd, line), free_cmd(cmd));
	while (prompt(&line))
	{
		parse_line(&cmd, line);
	}
	return (C_SUCCESS);
}
