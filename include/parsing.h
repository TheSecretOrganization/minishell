/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:06:06 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/24 15:46:58 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define CH_ERR "`#()\\[]{};!"
# define CH_SPCL "&|<>"
# define CH_OPE "&|"
# define CH_DIR "<>"

t_code	parse_line(t_data *data);

t_code	check_syntax(t_data *data);
t_code	error_syntax(t_code code, char *el, size_t n);

size_t	expand_variables(t_data *data, size_t i);

t_code	clean_memory(t_data *data, char *join_args);
char	*find_next_sep(char *line);
char	*fspace_njoin(char *s1, char *s2, size_t n);

t_code	create_ast(t_data *data);

#endif
