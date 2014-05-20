/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 00:24:30 by hestela           #+#    #+#             */
/*   Updated: 2014/04/24 07:12:20 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static void		ft_instring(char *quote, char c, int d)
{
	if (*quote == '\0' && ft_strchr("\"'", c))
		*quote = c;
	else if (*quote == c && d != '\\')
		*quote = '\0';
}

static int		ft_line_nbr(char *str)
{
	int			count;
	char		quote;

	count = 0;
	quote = '\0';
	while (*str)
	{
		ft_instring(&quote, *str, *(str - 1));
		while (*str == ' ')
		{
			str++;
			ft_instring(&quote, *str, *(str - 1));
		}
		if (*str == '\0')
			return (count);
		count++;
		while ((*str != ' ' || *(str - 1) == '\\' || quote != '\0')
			&& *str != '\0')
		{
			str++;
			ft_instring(&quote, *str, *(str - 1));
		}
	}
	return (count);
}

static char		*ft_ndup(char *s)
{
	int			size;
	char		*new;
	int			i;
	char		qt;

	qt = '\0';
	i = 0;
	size = 0;
	ft_instring(&qt, *(s + i), *(s + i - 1));
	while ((*(s + i) != ' ' || qt != '\0' || *(s + i - 1) == '\\')
		&& *(s + i) != '\0' && size++ >= 0 && i++ >= 0)
		ft_instring(&qt, *(s + i), *(s + i - 1));
	new = (char*)malloc(sizeof(*new) * size + 1);
	i = 0;
	qt = '\0';
	ft_instring(&qt, *(s + i), *(s + i - 1));
	while ((*(s + i) != ' ' || qt != '\0' || *(s + i - 1) == '\\')
		&& *(s + i) != '\0')
	{
		new[i] = *(s + i);
		i++;
		ft_instring(&qt, *(s + i), *(s + i - 1));
	}
	new[i] = '\0';
	return (new);
}

static void		ft_del_quote(char **av, int i, int j, int l)
{
	char		*string;

	while (av[i++])
	{
		j = 0;
		l = 0;
		if (ft_strchr(av[i - 1], '"') || ft_strchr(av[i - 1], '\''))
		{
			string = ft_strdup(av[i - 1]);
			string[ft_strlen(string) - 1] = '\0';
			string++;
			free(av[i - 1]);
			av[i - 1] = ft_strdup(string);
			string--;
			free(string);
		}
		while (av[i - 1][j])
		{
			if (av[i - 1][l] == '\\' && ft_strchr("\"' `", av[i - 1][l + 1]))
				l++;
			av[i - 1][j] = av[i - 1][l];
			j++;
			l++;
		}
	}
}

char			**ft_split_args(char *str, int i)
{
	char		**array;
	int			lines;
	char		quote;

	quote = '\0';
	lines = ft_line_nbr(str);
	array = (char**)malloc(sizeof(*array) * (lines + 1));
	array[lines] = '\0';
	while (i < lines)
	{
		while (*str == ' ')
			str++;
		ft_instring(&quote, *str, *(str - 1));
		array[i] = ft_ndup(str);
		while ((*str != ' ' || quote != '\0' || *(str - 1) == '\\')
			&& *str != '\0')
		{
			str++;
			ft_instring(&quote, *str, *(str - 1));
		}
		i++;
	}
	ft_del_quote(array, 0, 0, 0);
	return (array);
}
