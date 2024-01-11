/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:30 by averin            #+#    #+#             */
/*   Updated: 2024/01/11 22:10:59 by abasdere         ###   ########.fr       */
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

# define TYPE_CMD 1
# define TYPE_INFILE 2
# define TYPE_OUTFILE 3
# define TYPE_PIPE 4
# define TYPE_PIPE_AND 5
# define TYPE_PIPE_OR 6

# define ERR_GEN "error"
# define ERR_MEM "memory allocation failled"

typedef enum e_code
{
	C_SUCCES = 0,
	C_ERR_GEN = 1,
	C_BAD_USE = 2,
	C_ERR_MEM = 3
}	t_code;

typedef struct s_element
{
	int		type;
	void	*value;
}	t_element;

typedef struct s_cmd
{
	char		**args;
	t_element	*elements;
}	t_cmd;

t_code	error(t_code code, char *el, char *message);
char	*prompt(char **line);
void	register_signals(void);

#endif
