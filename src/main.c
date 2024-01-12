/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/01/12 19:20:59 by abasdere         ###   ########.fr       */
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
	while (prompt(&line))
	{
		parse_line(&cmd, line);
	}
	return (0);
}
