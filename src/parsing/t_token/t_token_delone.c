/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_delone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:58:31 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/11 12:45:28 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Delete a t_token node
 * @param lst node to destroy
*/
void	t_token_delone(t_token *lst)
{
	if (!lst)
		return ;
	free(lst);
}
