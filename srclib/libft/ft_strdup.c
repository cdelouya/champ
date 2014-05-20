/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 08:38:57 by hestela           #+#    #+#             */
/*   Updated: 2014/02/28 17:25:51 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;

	copy = NULL;
	copy = (char*)ft_memalloc(ft_strlen(s1) + 1);
	if (copy)
		ft_strcpy(copy, s1);
	return (copy);
}
