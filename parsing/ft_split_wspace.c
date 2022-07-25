/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_wspace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 03:26:56 by asimon            #+#    #+#             */
/*   Updated: 2022/07/25 19:01:47 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/parsing.h"

static int	ft_word_len(char const *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (is_wspace(s[i]))
			return (i);
		i++;
	}
	return (i);
}

static int	ft_word_count(char const *s)
{
	int	i;
	int	words;

	if (ft_strlen(s) == 0)
		return (0);
	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (!is_wspace(s[i]) && s[i] != '\0')
		{
			if (is_wspace(s[i + 1]) && !is_wspace(s[i]))
				words++;
			i++;
		}
		while (s[i] != '\0' && is_wspace(s[i]))
			i++;
	}
	if (!is_wspace(s[i - 1]))
		words++;
	return (words);
}

static int	ft_cpy_in_tab(char *tab, char const *s, int i)
{
	int	x;

	x = 0;
	while (!is_wspace(s[i]) && s[i])
	{
		tab[x] = s[i];
		i++;
		x++;
	}
	tab[x] = '\0';
	return (i);
}

static void	*free_tab(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	**ft_split_wspace(char *s)
{
	int		i;
	int		j;
	char	**tab;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	tab = malloc(sizeof(tab) * (ft_word_count(s) + 1));
	if (!tab)
		return (NULL);
	while (j < ft_word_count(s))
	{
		while (is_wspace(s[i]) && s[i])
			i++;
		tab[j] = malloc(sizeof(char) * (ft_word_len(s + i) + 1));
		if (!tab[j])
			return (free_tab(tab, j));
		i = ft_cpy_in_tab(tab[j], s, i);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
