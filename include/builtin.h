/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:55:29 by averin            #+#    #+#             */
/*   Updated: 2024/02/13 17:20:47 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "execution.h"

int		cmd_echo(t_exec *exec);
int		cmd_cd(t_exec *exec);
int		cmd_pwd(t_exec *exec);
int		ft_getcwd(char **cwd);
int		cmd_export(t_exec *exec);
int		check_arg(char *arg, char **value);
void	print_export(char *arg, int outfile);
int		cmd_unset(t_exec *exec);
int		cmd_env(t_exec *exec);
int		cmd_exit(t_exec *exec);

#endif
