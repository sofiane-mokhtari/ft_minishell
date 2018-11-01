/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:48:58 by smokhtar          #+#    #+#             */
/*   Updated: 2018/08/23 14:48:59 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(t_envt *e, char *need)
{
	int		i;
	char	**tab;
	char	*str;

	i = 0;
	str = NULL;
	while (e->env[i])
	{
		if (!(tab = ft_strsplit(e->env[i], '=')))
			ft_error(0);
		if (ft_strcmp(tab[0], need) == 0)
		{
			if (!(str = ft_strdup(tab[1])))
				ft_error(0);
			ft_tabdel(tab);
			return (str);
		}
		ft_tabdel(tab);
		i++;
	}
	return (NULL);
}

void	ft_echo(t_input *in)
{
	int		i;

	i = 0;
	while (in->av[++i])
	{
		if (in->av[i][0] == '$')
		{
			if (!in->av[i][1])
				ft_putchar('$');
		}
		else
			ft_putstr(in->av[i]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	ft_unsetenv(t_envt *e, char *sup)
{
	char	*s;
	char	**tab;
	int		i;
	int		j;

	if (!(sup))
		return ;
	if (!(s = find_env(e, sup)))
		return ;
	free(s);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (ft_tablen(e->env)))))
		ft_error("malloc error");
	i = -1;
	j = 0;
	while (e->env[++i])
	{
		if (ft_strcmp(e->env[i], sup) != '=')
			if (!(tab[j++] = ft_strdup(e->env[i])))
				ft_error("malloc error");
	}
	tab[j] = NULL;
	ft_tabdel(e->env);
	e->env = tab;
}

void	ft_setenv(t_envt *e, t_input *in)
{
	char	**cpy;
	int		i;
	int		len;

	if (in->ac != 2)
		return ;
	len = ft_tablen(e->env);
	ft_unsetenv(e, in->av[1]);
	if (!(cpy = (char**)ft_memalloc(sizeof(char*) * (len + 2))))
		ft_error("malloc error");
	cpy[len + 1] = NULL;
	i = 0;
	while (e->env[i])
	{
		if (!(cpy[i] = ft_strdup(e->env[i])))
			ft_error("malloc error");
		i++;
	}
	cpy[i] = ft_strnew(ft_strlen(in->av[1]) + ft_strlen(in->av[2]) + 2);
	ft_strcat(ft_strcat(ft_strcat(cpy[i], in->av[1]), "="), in->av[2]);
	ft_tabdel(e->env);
	e->env = cpy;
}
