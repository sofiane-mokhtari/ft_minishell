/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwhitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 14:10:47 by smokhtar          #+#    #+#             */
/*   Updated: 2018/09/12 14:10:49 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\r' || c == 9);
}

static int		ft_count_splitted(const char *s)
{
	int		count;
	size_t	idx;
	char	l_c;

	if (!ft_strlen(s))
		return (0);
	count = 1;
	idx = 0;
	l_c = 0;
	while (s[idx])
	{
		if (ft_is_whitespace(s[idx]) && l_c != 0 && !ft_is_whitespace(l_c))
			count++;
		l_c = s[idx];
		idx++;
	}
	if (ft_is_whitespace(l_c))
		count--;
	return (count);
}

static size_t	ft_strlen_split(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != 0 && !ft_is_whitespace(s[len]))
		len++;
	return (len);
}

static char		*ft_extract_word(const char *s, size_t *sidx)
{
	char	*res;
	size_t	idx;
	size_t	len;

	len = ft_strlen_split(s + *sidx);
	if ((res = ft_strnew(len)) == 0)
		return (0);
	idx = 0;
	while (idx < len)
		res[idx++] = s[(*sidx)++];
	return (res);
}

char			**ft_split_whitespace(const char *s)
{
	char	**tab;
	size_t	idx;
	size_t	sidx;
	size_t	count;

	if (s == 0)
		return (0);
	count = ft_count_splitted(s);
	if ((tab = ft_memalloc(sizeof(char *) * (count + 1))) == 0)
		return (0);
	idx = 0;
	sidx = 0;
	while (idx < count)
	{
		while (ft_is_whitespace(s[sidx]))
			sidx++;
		tab[idx] = ft_extract_word(s, &sidx);
		idx++;
	}
	return (tab);
}
