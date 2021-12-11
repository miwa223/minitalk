/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:29:17 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/11/22 18:32:16 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	initialize_tags(t_tag *tag)
{
	tag->flag[0] = 0;
	tag->flag[1] = 0;
	tag->field = -1;
	tag->prec = -1;
	tag->type = '\0';
	tag->len = 0;
	tag->error = 0;
}

int	output_character(va_list *ap, t_tag *tag, char *format, int j)
{
	int	d;

	d = 0;
	if (tag->type == 'd' || tag->type == 'i')
		output_int(ap, tag);
	else if (tag->type == 'c')
		output_char(ap, tag);
	else if (tag->type == 's')
		output_str(ap, tag);
	else if (tag->type == 'u' || tag->type == 'x' || tag->type == 'X'
		|| tag->type == 'p' || tag->type == '%')
	{
		if (output_unsigned_int(ap, tag) == -2)
			return (-2);
	}
	while (format[j] != '\0' && (format[j] != '%' || tag->type == '\0'))
	{
		write(1, &format[j], 1);
		tag->print_len++;
		j++;
	}
	if (format[j] == '%')
		return (j);
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_tag	tag;
	int		i;

	i = 0;
	va_start(ap, format);
	if (!format)
		return (-1);
	tag.print_len = 0;
	while (i > -1)
	{
		initialize_tags(&tag);
		i = prep_tags(&ap, &tag, (char *)format, i);
		if (i == 0)
			break ;
		i = output_character(&ap, &tag, (char *)format, i);
	}
	va_end(ap);
	return (tag.print_len);
}
