/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:06:06 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/12 19:29:29 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_val
{
	V_ERROR = 0,
	V_SEP = 1,
	V_CHAR = 2,
	V_WILDCARD = 3,
	V_VARIABLE = 4,
	V_QUOTE = 5,
	V_DQUOTE = 6,
	V_SPCL_CHAR = 7
}	t_val;

typedef struct s_token
{
	t_val			val;
	char			*id;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void	t_token_addback(t_token **tk, t_token *new);
void	t_token_clear(t_token **tk);
t_token	*t_token_last(t_token *tk);
t_token	*t_token_new(char *id);
void	t_token_print_vals(t_token *tk);
size_t	t_token_size(t_token *tk);

t_code	clean_memory(t_code code, t_cmd *cmd, char *line, t_token **tk);
t_code	error_syntax(t_code code, char el);
t_code	parse_line(t_cmd **cmd, char *line);

#endif
