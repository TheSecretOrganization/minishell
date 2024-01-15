/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:17:31 by averin            #+#    #+#             */
/*   Updated: 2024/01/15 11:06:44 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

int	exec_cmd(t_cmd *cmd, char **path);
int	do_exec(char *exec, char **args, char **envp, int *fds);

#endif
