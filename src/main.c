/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/01/11 19:54:19 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	main(void)
{
	char	*line;
	t_cmd	cmd;

	line = NULL;
	cmd.args = NULL;
	cmd.elements = NULL;
	register_signals();
	while (prompt(&line))
	{
		if (!parse_line(&cmd, line))
			return (free(line), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
