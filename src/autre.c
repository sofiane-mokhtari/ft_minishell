/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autre.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 14:33:58 by smokhtar          #+#    #+#             */
/*   Updated: 2018/09/12 14:33:59 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tabdup(char **tab)
{
	char	**cpy;
	int		i;

	if (!(cpy = (char**)ft_memalloc(sizeof(char*) * (ft_tablen(tab) + 1))))
		return (NULL);
	i = -1;
	while (tab[++i])
		if (!(cpy[i] = ft_strdup(tab[i])))
			return (NULL);
	cpy[i] = NULL;
	return (cpy);
}

t_pwd	*get_last(t_pwd *st)
{
	while (st->next)
		st = st->next;
	return (st);
}

void	free_path_one(t_pwd *pwd)
{
	free(pwd->dir);
	if (pwd->next)
		pwd->next->prev = NULL;
	if (pwd->prev)
		pwd->prev->next = NULL;
	pwd->prev = NULL;
	pwd->next = NULL;
	pwd->dir = NULL;
	free(pwd);
}

void	free_path(t_pwd *pwd)
{
	t_pwd	*tmp;

	while (pwd)
	{
		tmp = pwd->next;
		free(pwd->dir);
		pwd->prev = NULL;
		pwd->next = NULL;
		pwd->dir = NULL;
		free(pwd);
		pwd = tmp;
	}
}
