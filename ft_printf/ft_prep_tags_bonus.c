/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prep_tags_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:28:55 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/11/13 20:29:18 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	set_flag(t_tag *tag, char *format, int i)
{
	while (format[i] == '-' || format[i] == '0')
	{
		if (format[i] == '-')
			tag->flag[0] = 1;
		else if (format[i] == '0')
			tag->flag[1] = 1;
		i++;
	}
	return (i);
}

int	has_asterisk(va_list *ap, t_tag *tag, int flag, int i)
{
	int	num;

	num = va_arg(*ap, int);
	if (num < 0 && flag == 1)
		tag->prec = -1;
	else if (flag == 1)
		tag->prec = num;
	else if (num < 0)
	{
		tag->field = num * (-1);
		tag->flag[0] = 1;
	}
	else
		tag->field = num;
	return (i + 1);
}

int	no_asterisk(t_tag *tag, int flag, int i, char *format)
{
	int	num;

	num = 0;
	while (format[i] >= '0' && format[i] <= '9')
	{
		num = num * 10 + (format[i] - '0');
		i++;
	}
	if (flag == 1)
		tag->prec = num;
	else
		tag->field = num;
	return (i);
}

int	set_field_prec(va_list *ap, t_tag *tag, char *format, int i)
{
	int	num;
	int	flag;

	num = 0;
	flag = 0;
	while (flag == 0)
	{
		if (format[i] != '.' && tag->field != -1)
			break ;
		if (format[i] == '.')
		{
			flag = 1;
			i++;
		}
		if (format[i] == '*')
			i = has_asterisk(ap, tag, flag, i);
		else if (format[i] != '*')
			i = no_asterisk(tag, flag, i, format);
	}
	return (i);
}

int	prep_tags(va_list *ap, t_tag *tag, char *format, int i)
{
	int		n;
	char	*str;

	n = 0;
	str = "cspdiuxX%";
	while (format[i] != '%')
	{
		if (format[i] == '\0')
			return (0);
		tag->print_len += write(1, &format[i++], 1);
	}
	i = set_flag(tag, (char *)format, i + 1);
	i = set_field_prec(ap, tag, (char *)format, i);
	if (format[i] == '\0')
		return (0);
	while (str[n] != '\0')
	{
		if (str[n] == format[i])
			tag->type = str[n];
		n++;
	}
	if (tag->type == '\0')
		return (i);
	return (i + 1);
}
