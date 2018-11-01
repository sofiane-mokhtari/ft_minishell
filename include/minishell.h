/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:15:15 by smokhtar          #+#    #+#             */
/*   Updated: 2018/08/23 14:15:18 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include "/usr/include/sys/syslimits.h"
# include <sys/stat.h>

int					g_ptn;

typedef struct		s_input
{
	int				ac;
	char			**av;
}					t_input;

typedef struct		s_pwd
{
	char			*dir;
	struct s_pwd	*prev;
	struct s_pwd	*next;
}					t_pwd;

typedef struct		s_envt
{
	char			*name;
	t_pwd			*path;
	t_pwd			*p_path;
	char			**env;
}					t_envt;

void				ft_puterror(char *s1, char *s2, char *s3, char *s4);
void				print_list(t_pwd *l);

/*
**		input
*/

void				input(t_envt *e);
void				verif(t_envt *e, t_input *in);

/*
**		pars
*/

t_input				*pars(t_envt *e, char *str);
void				pars_m(t_envt *e, char **tab);

/*
**		ft_splitwhitespace
*/

char				**ft_split_whitespace(const char *s);

/*
**		env
*/

void				ft_env(t_envt *e, t_input *in);

/*
**		builtins
*/

char				*find_env(t_envt *e, char *need);
void				ft_echo(t_input *in);
void				ft_unsetenv(t_envt *e, char	*sup);
void				ft_setenv(t_envt *e, t_input *in);

/*
**		buildin_cd
*/

void				ft_cd(t_envt *e, t_input *in);
t_pwd				*str_to_path(char *str);
char				*path_to_str(t_pwd *pwd);

/*
**		buildin_cd_2
*/

int					test_chdir(char *pwd, char *name);
void				new_t_pwd(t_pwd **new, char *dir);
void				add_dir(t_pwd *l, char *dir);
void				go_home(t_envt *e);
void				start_slash(t_envt *e, t_input *in);

/*
**		fork
*/

void				ft_exec(t_envt *e, char **av, int mode);
void				ft_exec_2(t_envt *e, char **av, int mode);

/*
**		autre
*/

char				**ft_tabdup(char **tab);
void				free_path(t_pwd *pwd);
void				free_path_one(t_pwd *pwd);
t_pwd				*get_last(t_pwd *st);

#endif
