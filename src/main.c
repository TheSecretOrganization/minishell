/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:12 by averin            #+#    #+#             */
/*   Updated: 2024/01/11 22:26:56 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	main(void)
{
	char	*line;
	t_cmd	cmd;
	t_code	code;

	line = NULL;
	cmd.args = NULL;
	cmd.elements = NULL;
	code = C_SUCCES;
	register_signals();
	while (prompt(&line))
	{
		if (parse_line(&code, &cmd, line))
			return (free(line), code);
	}
	return (code);
}
