/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:55:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 11:32:14 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Find the last node of a t_token list
 * @param tk head of the list
 * @return t_token * or NULL if tk is NULL
*/
t_token	*t_token_last(t_token *tk)
{
	if (!tk)
		return (NULL);
	while (tk->next)
		tk = tk->next;
	return (tk);
}
