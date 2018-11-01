/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:16:57 by smokhtar          #+#    #+#             */
/*   Updated: 2018/09/10 14:16:58 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		go_ex(t_envt *e, char **av, char *path, int mode)
{
	pid_t	pid;
	char	**cpy;

	if (mode && *(e->env))
	{
		if (!(cpy = ft_tabdup(e->env)))
			ft_error("malloc error\n");
	}
	else
	{
		if (!(cpy = (char**)ft_memalloc(sizeof(char*) * 1)))
			ft_error("malloc error\n");
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, av, cpy) == -1)
			ft_error("fork error1\n");
	}
	else if (pid)
		wait(0);
	else
		ft_error("fork error2\n");
	if (mode && *(e->env))
		ft_tabdel(cpy);
}

char		*test_ifbin2(char *pwd, char *bin)
{
	char		path[PATH_MAX];
	char		*str;
	struct stat	sb;

	str = NULL;
	ft_memset(path, '\0', PATH_MAX);
	ft_strcat(ft_strcat(ft_strcat(path, pwd), "/"), bin);
	if (stat(path, &sb) != -1)
		if (!(str = ft_strdup(path)))
			ft_error("malloc error\n");
	ft_strclr(path);
	return (str);
}

void		test_ifbin(t_envt *e, char **av, char *tmpp, int mode)
{
	char	**pwd;
	int		i;

	i = 0;
	if (!(pwd = ft_strsplit(tmpp, ':')))
		ft_error("malloc error\n");
	free(tmpp);
	while (pwd[i])
		if ((tmpp = test_ifbin2(pwd[i++], av[0])))
			break ;
	ft_tabdel(pwd);
	if (!(tmpp))
	{
		ft_puterror(e->name, ": command not found: ", av[0], "\n");
		g_ptn = 1;
		return ;
	}
	go_ex(e, av, tmpp, mode);
	free(tmpp);
}

void		ft_exec_2(t_envt *e, char **av, int mode)
{
	char		*p;
	struct stat	sb;

	p = av[0] + 2;
	if (stat(p, &sb) != -1)
	{
		if (!(S_ISDIR(sb.st_mode)))
		{
			if (sb.st_mode & S_IXOTH)
				go_ex(e, av, p, mode);
			else
				ft_puterror(e->name, ": permission denied: ", p, "\n");
		}
		else
			ft_puterror(e->name, ": ", av[0], ": is a directory\n");
	}
	else
	{
		ft_puterror(e->name, ": command not found: ", p, "\n");
		g_ptn = 1;
	}
}

void		ft_exec(t_envt *e, char **av, int mode)
{
	char	*tmpp;

	if ((tmpp = test_ifbin2("", av[0])))
	{
		go_ex(e, av, tmpp, mode);
		free(tmpp);
		return ;
	}
	if (!(tmpp = find_env(e, "PATH")))
		ft_puterror(e->name, ": command not found: ", av[0], "\n");
	else
	{
		test_ifbin(e, av, tmpp, mode);
		tmpp = NULL;
	}
}
