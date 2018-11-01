/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:33:38 by smokhtar          #+#    #+#             */
/*   Updated: 2018/08/23 14:33:39 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			verif(t_envt *e, t_input *in)
{
	g_ptn = 2;
	if (ft_strcmp(in->av[0], "cd") == 0)
		ft_cd(e, in);
	else if (ft_strcmp(in->av[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(in->av[0], "echo") == 0)
	{
		if (in->ac == 0)
			ft_putchar('\n');
		else
			ft_echo(in);
	}
	else if (ft_strcmp(in->av[0], "env") == 0)
		ft_env(e, in);
	else if (ft_strcmp(in->av[0], "unsetenv") == 0)
		ft_unsetenv(e, in->av[1]);
	else if (ft_strcmp(in->av[0], "setenv") == 0)
		ft_setenv(e, in);
	else if (in->av[0][0] == '.' && in->av[0][1] && in->av[0][1] == '/')
		ft_exec_2(e, in->av, 1);
	else
		ft_exec(e, in->av, 1);
	ft_tabdel(in->av);
	free(in);
	g_ptn = 1;
}

static void		sighandler(int signum)
{
	if (signum == 2)
	{
		ft_putstr("\n");
		if (g_ptn != 2)
			ft_putstr("$>");
	}
}

void			input(t_envt *e)
{
	char		*str;
	char		*ver;
	t_input		*in;
	char		**tab;

	signal(SIGINT, &sighandler);
	while (1)
	{
		if (g_ptn)
			ft_putstr("$>");
		g_ptn = 1;
		if (get_next_line(0, &str) <= 0)
			exit(0);
		if (!(ver = ft_strdup(str)))
			ft_error("malloc error\n");
		else if ((tab = ft_strsplit(ver, ';')) && ft_tablen(tab) > 1)
			pars_m(e, tab);
		else if (ft_strlen(ver) != 0 && (in = pars(e, ver)))
			verif(e, in);
		ft_tabdel(tab);
		free(ver);
		free(str);
	}
}
