/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:12 by averin            #+#    #+#             */
/*   Updated: 2024/02/02 18:42:01 by abasdere         ###   ########.fr       */
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

static t_code	print_export(char **envp)
{
	t_data	cpy;
	size_t	i;

	if (cpy_envp(&cpy, envp))
		return (C_MEM);
	i = 0;
	while (cpy.envp[i])
		i++;
	quicksort(cpy.envp, i);
	i = 0;
	while (cpy.envp[i])
		printf("export %s\n", cpy.envp[i++]);
	return (ft_fsplit(cpy.envp), C_SUCCESS);
}

int	cmd_export(t_exec *exec)
{
	if (exec->args[0] == NULL)
		return (C_SUCCESS);
	else if (exec->args[1] == NULL)
		return (print_export(exec->data->envp));
	return (C_SUCCESS);
}
