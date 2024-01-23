/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/01/23 11:06:06 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	main(void)
{
	char	*line;
	t_cmd	*cmd;
	int		status;

	line = NULL;
	cmd = NULL;
	status = 0;
	register_signals();
	while (prompt(&line, status))
	{
		status = parse_line(&cmd, line);
		if (status == C_BAD_USE)
			continue ;
	}
	return (C_SUCCESS);
}
