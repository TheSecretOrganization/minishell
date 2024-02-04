/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:10:41 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/03 22:05:50 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void	quicksort(char **envp, size_t len)
{
	size_t	i;
	size_t	piv;

	i = -1;
	piv = 0;
	if (len <= 1)
		return ;
	while (++i < len)
		if (ft_strncmp(envp[i], envp[len -1], ft_strlen(envp[i])) < 0)
			swap(envp + i, envp + piv++);
	swap(envp + piv, envp + len - 1);
	quicksort(envp, piv++);
	quicksort(envp + piv, len - piv);
}

int	print_export(char **envp)
{
	t_data	cpy;
	char	*eql;
	char	*last;
	size_t	i;

	if (cpy_envp(&cpy, envp))
		return (C_MEM);
	i = -1;
	while (cpy.envp[++i])
		;
	(quicksort(cpy.envp, i), i = -1);
	while (cpy.envp[++i])
	{
		(ft_putstr_fd("export ", 1), eql = ft_strchr(cpy.envp[i], '='));
		if (!eql && printf("%s\n", cpy.envp[i]))
			continue ;
		(write(1, cpy.envp[i], ++eql - cpy.envp[i]), ft_putchar_fd('\"', 1));
		last = ft_strchr(cpy.envp[i], '\0');
		(write(1, eql, last - eql), ft_putendl_fd("\"", 1));
	}
	return (ft_fsplit(cpy.envp), C_SUCCESS);
}

char	*delete_char(char *s, char c)
{
	size_t	i;
	char	*tmp;

	tmp = ft_strchr(s, c);
	while (tmp)
	{
		ft_memmove
		tmp = ft_strchr(s, c);
	}
	return (ft_substr(s, 0, ft_strlen(s)));
}

int	remove_quotes(char **arg)
{
	char	*tmp;

	if (ft_strchr(*arg, '\"'))
	{
		tmp = delete_char(*arg, '\"');
		if (!tmp)
			return (C_MEM);
		(free(*arg), *arg = tmp);
	}
	if (ft_strchr(*arg, '\''))
	{
		tmp = delete_char(*arg, '\'');
		if (!tmp)
			return (C_MEM);
		(free(*arg), *arg = tmp);
	}
	return (C_SUCCESS);
}
