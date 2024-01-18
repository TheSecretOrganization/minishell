/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:06:06 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/18 11:16:26 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define CH_ERR "~`#()\\[]{};?!"
# define CH_OPE "&|"
# define CH_DIR "<>"

void	clean_memory(t_cmd *cmd, char *line, char **args);
t_code	error_syntax(t_code code, char *el, size_t n);
t_code	parse_line(t_cmd **cmd, char *line);

#endif
