/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:06:06 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/15 14:07:36 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define CH_ERR "`#()[]{};!\\*"
# define CH_SPCL "&|<>"
# define CH_OPE "&|"
# define CH_DIR "<>"

typedef struct s_ast
{
	t_cmd	*target;
	char	**args;
	size_t	i;
}	t_ast;

typedef struct s_quotes
{
	size_t	nq;
	size_t	nd;
	int		e;
	int		h;
}	t_quotes;

t_code	parse_line(t_data *data);
int		ft_is_space(char c);

t_code	error_syntax(t_code code, char *el, size_t n);
t_code	check_syntax(t_data *data);
t_code	check_spcl_chars(char *line);
t_code	check_in(char *line, size_t *pos, t_bool force_err);
t_code	check_out(char *line, size_t *pos, t_bool force_err);
int		check_hd(char *s, size_t i);

char	*expand_variable(t_data *data, size_t i, int add_q);
char	*expand_status(t_data *data, int add_q);
t_code	expand_var(t_data *data, size_t i);
int		expand(t_data *d);
char	*join_and_replace(char *line, char *td, char *tr, int add_q);

int		remove_quotes(char *s);

t_code	create_ast(t_data *data);
t_code	o_init_cmd(t_cmd **cmd);
t_code	add_ope(t_ast *ast);
t_code	add_dir(t_ast *ast);
char	**split_line(char *line);
void	free_args(t_ast *ast);

#endif
