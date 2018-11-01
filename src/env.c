/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 17:38:30 by smokhtar          #+#    #+#             */
/*   Updated: 2018/10/01 17:38:31 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_i(t_envt *e, t_input *in)
{
	char	**tab;

	if (in->ac < 2)
		return ;
	tab = in->av;
	tab += 2;
	if (in->av[0] && in->av[0][0] == '.' && in->av[0][1] && in->av[0][1] == '/')
		ft_exec_2(e, tab, 0);
	else
		ft_exec(e, tab, 0);
}

void		ft_env(t_envt *e, t_input *in)
{
	if (in->ac == 0)
		ft_puttable(e->env);
	else if (in->ac == 2)
	{
		if (ft_strcmp(in->av[1], "-i") == 0)
			env_i(e, in);
		else
		{
			ft_setenv(e, in);
			ft_puttable(e->env);
		}
	}
	else
		ft_putstr_fd("usage error\n", 2);
}
