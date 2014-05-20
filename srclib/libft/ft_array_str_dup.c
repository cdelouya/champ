/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_str_dup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 21:52:24 by hestela           #+#    #+#             */
/*   Updated: 2014/02/28 17:17:19 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char			**ft_array_str_dup(char **array)
{
	char		**copy;
	int			i;

	copy = NULL;
	i = 0;
	if (array && *array)
	{
		copy = (char**)malloc(sizeof(*copy) * ft_array_str_len(array) + 1);
		while (i < (int)ft_array_str_len(array))
		{
			copy[i] = ft_strdup(array[i]);
			i++;
		}
		copy[i] = '\0';
	}
	return (copy);
}
