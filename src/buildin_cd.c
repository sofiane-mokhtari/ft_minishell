/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 15:17:42 by smokhtar          #+#    #+#             */
/*   Updated: 2018/09/11 15:17:44 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			add_to_path(t_envt *e, char **tab, char *pwd)
{
	int		i;
	char	*p;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "..") == 0)
			free_path_one(get_last(e->path));
		else if (ft_strcmp(tab[i], "~") == 0)
		{
			free_path(e->p_path);
			e->p_path = e->path;
			e->path = NULL;
			if (!(p = find_env(e, "HOME")))
				ft_putstr_nl("cd: HOME not set");
			e->path = str_to_path(p);
			free(p);
		}
		else if (ft_strcmp(tab[i], ".") != 0)
			add_dir(get_last(e->path), tab[i]);
		i++;
	}
	p = path_to_str(e->path);
	test_chdir(p, pwd);
	free(p);
}

static void		switch_pwd(t_pwd **n, t_pwd **p)
{
	t_pwd	*tmp;

	tmp = *n;
	*n = *p;
	*p = tmp;
}

void			ft_cd(t_envt *e, t_input *in)
{
	char	*p;
	char	**tab;

	if (in->ac == 0 || (in->av && in->av[1] && ft_strcmp(in->av[1], "~") == 0))
		go_home(e);
	else if (in->av && in->av[1] && ft_strcmp(in->av[1], "-") == 0)
	{
		if (e->p_path == NULL)
			return ;
		switch_pwd(&(e->path), &(e->p_path));
		if (chdir(p = path_to_str(e->path)) != 0)
			ft_error("chdir error\n");
		ft_putstr_nl(p);
		free(p);
	}
	else if (in->av && in->av[1] && in->av[1][0] == '/')
		start_slash(e, in);
	else
	{
		if (!(tab = ft_strsplit(in->av[1], '/')))
			ft_error("malloc error\n");
		add_to_path(e, tab, in->av[1]);
		ft_tabdel(tab);
	}
}

t_pwd			*str_to_path(char *str)
{
	char	**tab;
	int		i;
	t_pwd	*stt;

	i = 0;
	stt = NULL;
	if (!(tab = ft_strsplit(str, '/')))
		return (NULL);
	while (tab[i])
		new_t_pwd(&stt, tab[i++]);
	ft_tabdel(tab);
	return (stt);
}

char			*path_to_str(t_pwd *pwd)
{
	char	*str;
	char	*tmp;

	if (!(tmp = ft_strdup("/")))
		return (NULL);
	if (!(str = ft_strjoin(tmp, pwd->dir)))
		return (NULL);
	free(tmp);
	while (pwd->next)
	{
		if (!(tmp = ft_strjoin(str, "/")))
			return (NULL);
		free(str);
		if (!(str = ft_strjoin(tmp, pwd->next->dir)))
			return (NULL);
		free(tmp);
		pwd = pwd->next;
	}
	return (str);
}
