/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:47:21 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 11:32:14 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Calculate the size of a t_token list
 * @param tk head of the list
 * @return size_t or 0 is tk is NULL
*/
size_t	t_token_size(t_token *tk)
{
	size_t	i;

	i = 1;
	if (!tk)
		return (0);
	while (tk->next && i++)
		tk = tk->next;
	return (i);
}
