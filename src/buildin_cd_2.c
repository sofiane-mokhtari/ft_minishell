/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 15:32:11 by smokhtar          #+#    #+#             */
/*   Updated: 2018/09/18 15:32:13 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		test_chdir(char *pwd, char *name)
{
	if (chdir(pwd) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

void	new_t_pwd(t_pwd **stt, char *dir)
{
	t_pwd	*tmp;
	t_pwd	*new;

	if (!(new = (t_pwd*)ft_memalloc(sizeof(t_pwd))))
		ft_error("malloc error\n");
	if (!(new->dir = ft_strdup(dir)))
		ft_error("malloc error\n");
	new->next = NULL;
	new->prev = NULL;
	if (*stt)
	{
		tmp = get_last(*stt);
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*stt = new;
}

void	add_dir(t_pwd *l, char *dir)
{
	t_pwd *new;

	if (!(new = (t_pwd*)ft_memalloc(sizeof(t_pwd))))
		ft_error("malloc error\n");
	new->dir = ft_strdup(dir);
	new->next = NULL;
	l->next = new;
	new->prev = l;
}

void	go_home(t_envt *e)
{
	char	*p;

	if (!(p = find_env(e, "HOME")))
	{
		ft_putstr_nl("cd: HOME not set");
		return ;
	}
	if (chdir(p) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: \n", 2);
		ft_putstr_fd(p, 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	free_path(e->p_path);
	e->p_path = e->path;
	e->path = NULL;
	if (!(e->path = str_to_path(p)))
		ft_error("malloc error\n");
	free(p);
}

void	start_slash(t_envt *e, t_input *in)
{
	if (test_chdir(in->av[1], in->av[1]))
	{
		free_path(e->p_path);
		e->p_path = e->path;
		e->path = str_to_path(in->av[1]);
	}
}
