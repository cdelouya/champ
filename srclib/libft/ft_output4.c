/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 08:46:07 by hestela           #+#    #+#             */
/*   Updated: 2014/03/26 19:14:46 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include "libft.h"

static void		ft_long(const char *form, va_list *ap, int **t, int *count)
{
	int			*i;
	int			precision;
	int			len;
	va_list		apcpy;

	i = t[0];
	precision = *t[1];
	len = 0;
	va_copy(apcpy, *ap);
	if (ft_strchr("lzh", form[*i]) && form[*i + 1] == 'o')
		len = ft_strlen(ft_itoa(ft_itoo(va_arg(apcpy, long))));
	else if (ft_strchr("lzh", form[*i]) && ft_strchr("udi", form[*i + 1]))
		len = ft_strlen(ft_itoa(va_arg(apcpy, long)));
	else if (ft_strchr("lzh", form[*i]) && ft_strchr("xX", form[*i + 1]))
		len = ft_strlen(ft_itoh(va_arg(apcpy, long)));
	while (len < precision)
	{
		*count += ft_putchar('0');
		len++;
	}
	ft_flags1(form, ap, i, count);
}

static void		ft_int(const char *form, va_list *ap, int **t, int *count)
{
	int			*i;
	int			precision;
	int			len;
	va_list		apcpy;

	i = t[0];
	precision = *t[1];
	len = 0;
	va_copy(apcpy, *ap);
	if (ft_strchr("dui", form[*i]))
		len = ft_strlen(ft_itoa(va_arg(apcpy, long)));
	if (ft_strchr("Xx", form[*i]))
		len = ft_strlen(ft_itoh(va_arg(apcpy, long)));
	if (ft_strchr("o", form[*i]))
		len = ft_strlen(ft_itoa(ft_itoo(va_arg(apcpy, long))));
	while (len < precision)
	{
		*count += ft_putchar('0');
		len++;
	}
	ft_flags1(form, ap, i, count);
}

static void		ft_float(const char *form, va_list *ap, int **t, int *count)
{
	int			*i;
	int			prec;

	i = t[0];
	prec = *t[1];
	if (form[*i] == 'f')
		*count += ft_putfnbr(va_arg(*ap, double), prec);
	else if (form[*i] == 'e')
		*count += ft_putstr(ft_dtos(va_arg(*ap, double), prec));
	else if (form[*i] == 'E')
		*count += ft_putstr(ft_str_upcase(ft_dtos(va_arg(*ap, double), prec)));
	else if (ft_strchr("lL", form[*i]))
	{
		if (form[*i] == 'l' && form[*i + 1] == 'f')
			*count += ft_putfnbr(va_arg(*ap, double), prec);
		else if (form[*i] == 'L' && form[*i + 1] == 'e')
			*count += ft_putstr(ft_dtos(va_arg(*ap, long double), prec));
		else if (form[*i] == 'L' && form[*i + 1] == 'E')
			*count += ft_putstr(ft_str_upcase\
								(ft_dtos(va_arg(*ap, long double), prec)));
		(*i)++;
	}
	*i += 2;
}

static void		ft_prec(const char *form, va_list *ap, int *i, int *count)
{
	int			precision;
	int			*tab[2];

	precision = 0;
	*i += 2;
	precision = va_arg(*ap, int);
	tab[0] = i;
	tab[1] = &precision;
	if (ft_strchr("eEf", form[*i])
		|| (ft_strchr("lL", form[*i]) && ft_strchr("eEf", form[*i + 1])))
		ft_float(form, ap, tab, count);
	else if (ft_strchr("xXdiuo", form[*i]))
		ft_int(form, ap, tab, count);
	else if (form[*i] == 's')
	{
		*count += ft_putnstr(va_arg(*ap, char*), precision);
		*i += 2;
	}
	else if (ft_strchr("lLzh", form[*i])
		&& ft_strchr("oudixX", form[*i + 1]))
		ft_long(form, ap, tab, count);
}

void			ft_flags4(const char *form, va_list *ap, int *i, int *count)
{
	if (form[*i] == '.' && form[*i + 1] == '*')
		ft_prec(form, ap, i, count);
	else
		ft_flags5(form, ap, i, count);
}
