/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:15:04 by smokhtar          #+#    #+#             */
/*   Updated: 2018/08/23 14:15:05 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_pwd *l)
{
	while (l)
	{
		ft_putstr(l->dir);
		ft_putchar('/');
		l = l->next;
	}
	ft_putchar('\n');
}

void	ft_puterror(char *s1, char *s2, char *s3, char *s4)
{
	ft_putstr_fd(s1, 2);
	if (s2)
	{
		ft_putstr_fd(s2, 2);
		if (s3)
		{
			ft_putstr_fd(s3, 2);
			if (s4)
				ft_putstr_fd(s4, 2);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_envt	*e;
	char	*str;

	if (!(e = (t_envt*)ft_memalloc(sizeof(t_envt))))
		ft_error("malloc error\n");
	if (!(e->env = ft_tabdup(env)))
		ft_error("malloc error\n");
	if (!(e->name = ft_strdup(av[0] + 2)))
		ft_error("malloc error\n");
	if ((str = find_env(e, "PWD")))
		e->path = str_to_path(str);
	e->p_path = NULL;
	g_ptn = 1;
	free(str);
	(void)ac;
	(void)av;
	input(e);
	return (0);
}
