/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:30 by averin            #+#    #+#             */
/*   Updated: 2024/01/15 15:49:38 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "libft.h"

# define PROMPT_HEAD "🦖"

# define M_ERROR "error"
# define M_MEM "memory allocation failled"

typedef enum e_code
{
	C_SUCCES = 0,
	C_GEN,
	C_BAD_USE,
	C_MEM,
}	t_code;

typedef enum e_type
{
	T_CMD = 1,
	T_INFILE = 2,
	T_OUTFILE = 3,
	T_PIPE = 4,
	T_PIPE_AND = 5,
	T_PIPE_OR = 6
}	t_type;

typedef struct s_element
{
	t_type	type;
	void	*value;
}	t_element;

typedef struct s_cmd
{
	char		**args;
	t_element	**elements;
}	t_cmd;

t_code	error(t_code code, char *el, char *message);
void	free_cmd(t_cmd *cmd);
char	*prompt(char **line);
void	register_signals(void);

#endif
