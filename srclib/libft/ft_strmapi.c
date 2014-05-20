/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 18:38:08 by hestela           #+#    #+#             */
/*   Updated: 2014/02/28 17:26:21 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	if (s && f)
	{
		str = (char*)ft_memalloc(ft_strlen(s) + 1);
		if (str)
		{
			while (*s)
			{
				str[i] = f((unsigned int)i, *s);
				s++;
				i++;
			}
			str[i] = '\0';
		}
	}
	return (str);
}
