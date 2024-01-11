/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:47:21 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/11 12:42:48 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Calculate the size of a t_token list
 * @param lst head of the list
 * @return size_t or 0 is lst is NULL
*/
size_t	t_token_size(t_token *lst)
{
	size_t	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst->next && i++)
		lst = lst->next;
	return (i);
}
