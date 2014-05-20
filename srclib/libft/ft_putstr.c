/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 09:26:24 by hestela           #+#    #+#             */
/*   Updated: 2014/03/26 18:40:19 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

int		ft_putstr(char const *s)
{
	int		i;

	i = 0;
	if (s)
	{
		i = ft_strlen(s);
		write(1, s, i);
		s++;
	}
	else
		i = ft_putstr("(null)");
	return (i);
}
