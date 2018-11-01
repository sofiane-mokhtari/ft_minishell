/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 17:35:22 by smokhtar          #+#    #+#             */
/*   Updated: 2018/10/01 17:35:23 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		replace_var(t_envt *e, t_input *in)
{
	int		i;
	char	*str;

	i = 0;
	while (in->av[i])
	{
		if (in->av[i][0] == '$')
		{
			if ((str = find_env(e, in->av[i] + 1)))
			{
				free(in->av[i]);
				if (!(in->av[i] = ft_strdup(str)))
					ft_error("malloc error\n");
				free(str);
			}
		}
		i++;
	}
}

t_input		*pars(t_envt *e, char *str)
{
	t_input	*input;

	if (!(input = (t_input*)ft_memalloc(sizeof(t_input))))
		ft_error("malloc error\n");
	if (!(input->av = ft_split_whitespace(str)))
		ft_error("malloc error\n");
	else
		replace_var(e, input);
	if (!(input->ac = ft_tablen(input->av)))
	{
		ft_tabdel(input->av);
		free(input);
		return (NULL);
	}
	if (input->ac > 0)
		input->ac--;
	return (input);
}

void		pars_m(t_envt *e, char **tab)
{
	int			i;
	t_input		*in;

	i = 0;
	while (tab[i])
	{
		if ((in = pars(e, tab[i])))
			verif(e, in);
		i++;
	}
}
