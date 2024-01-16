/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:17:31 by averin            #+#    #+#             */
/*   Updated: 2024/01/16 16:25:58 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "errno.h"

typedef struct s_exec
{
	char	**args;
	char	*pathname;
	int		pipes[2];
	int		infile;
	int		outfile;
}	t_exec;

int		dispatch_cmd(t_cmd *cmd, char **path);
int		do_exec(t_exec *exec, char **envp);
char	*find_relative_exec(char *cmd);
char	*find_path_exec(char *cmd, char **path);
char	**get_path(void);
void	free_exec(t_exec exec);

#endif
