/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:44:23 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/11 22:10:55 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Write error statement to stderr
 * @param code exit code to return
 * @param el element which caused the error, nullable
 * @param message error message details, nullable
 * @return t_code error code
*/
t_code	error(t_code code, char *el, char *message)
{
	ft_putstr_fd("🦕 :", STDERR_FILENO);
	if (el)
		ft_dprintf(STDERR_FILENO, " %s:", el);
	if (message)
		ft_dprintf(STDERR_FILENO, " %s", message);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (code);
}
