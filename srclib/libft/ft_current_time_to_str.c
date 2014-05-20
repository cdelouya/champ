/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_current_time_to_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/12 14:00:24 by hestela           #+#    #+#             */
/*   Updated: 2014/03/26 18:25:54 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

static char		*ft_suite(char **array)
{
	char		*str;
	char		*year;
	char		*tmp;
	int			i;

	i = 0;
	year = (char*)ft_memalloc(5);
	while (array[4][i] != '\n')
	{
		year[i] = array[4][i];
		i++;
	}
	year[4] = '\0';
	str = ft_strjoin(" ", year);
	free(year);
	tmp = ft_strdup(str);
	free(str);
	str = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_strdup(str);
	free(str);
	str = ft_strjoin(tmp, array[3]);
	free(tmp);
	return (str);
}

char			*ft_current_time_to_str(void)
{
	char		**array;
	char		*str;
	char		*tmp;
	time_t		clock;

	clock = time(NULL);
	array = ft_strsplit(ctime(&clock), ' ');
	str = ft_strjoin(array[0], " ");
	tmp = ft_strdup(str);
	str = ft_strjoin(tmp, array[2]);
	free(tmp);
	tmp = ft_strdup(str);
	free(str);
	str = ft_strjoin(tmp, " ");
	free(tmp);
	tmp = ft_strdup(str);
	free(str);
	str = ft_strjoin(tmp, array[1]);
	free(tmp);
	tmp = ft_strdup(str);
	free(str);
	str = ft_strjoin(tmp, ft_suite(array));
	free(tmp);
	return (str);
}
