/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/11 14:26:46 by hestela           #+#    #+#             */
/*   Updated: 2014/03/26 19:14:04 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>

double		ft_pow(double x, double y)
{
	return (exp(log(x) * y));
}
