/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_int_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:30:33 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 17:38:39 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_space(t_tag tag, int neg)
{
	int	i;

	i = 0;
	while (tag.flag[0] != 1 && tag.flag[1] != 1
		&& tag.field - neg > tag.prec + i && tag.field - neg > tag.len + i)
	{
		tag.print_len += write(1, " ", 1);
		i++;
	}
	while (tag.flag[0] != 1 && tag.flag[1] == 1 && tag.prec >= 0
		&& tag.field - neg > tag.prec + i && tag.field - neg > tag.len + i)
	{
		tag.print_len += write(1, " ", 1);
		i++;
	}
	if (tag.type == 'p' && tag.prec == 0 && tag.field >= tag.len)
		tag.print_len += write(1, " ", 1);
	return (tag.print_len);
}

unsigned int	set_len(va_list *ap, t_tag *tag, char **str)
{
	unsigned int	tmp;
	unsigned int	num;

	num = va_arg(*ap, unsigned int);
	if (tag->type == 'u')
	{
		tmp = num;
		if (tmp == 0 && tag->prec != 0)
			tag->len++;
		while (tmp > 0)
		{
			tmp /= 10;
			tag->len++;
		}
	}
	else if (tag->type == 'x' || tag->type == 'X')
	{
		if (convert_to_hex(num, str, *tag) == -2)
			tag->error = -2;
		if (!(num == 0 && tag->prec == 0))
			tag->len = ft_strlen_NULL(*str);
	}
	return (num);
}

int	check_ptr(va_list *ap, t_tag *tag, char **str)
{
	uintptr_t	num_ptr;

	if (tag->type == 'p')
	{
		num_ptr = va_arg(*ap, uintptr_t);
		if (convert_to_hex_ptr(num_ptr, str) == -2)
			return (-2);
		tag->len = ft_strlen_NULL(*str) + 2;
	}
	else if (tag->type == '%')
		 tag->len = 1;
	return (0);
}

int	output_unsigned_int(va_list *ap, t_tag *tag)
{
	unsigned int	num;
	char			*str;

	num = 0;
	str = NULL;
	if (check_ptr(ap, tag, &str) == -2)
		return (-2);
	else if (tag->type == 'u' || tag->type == 'x' || tag->type == 'X')
	{
		num = set_len(ap, tag, &str);
		if (tag->error == -2)
			return (-2);
	}
	tag->print_len = print_space(*tag, 0);
	if (tag->type == 'p')
		write(1, "0x", 2);
	if (tag->flag[0] == 1)
		exist_flag0_u(tag, (long)num, str, 0);
	else if (tag->flag[1] == 1)
		exist_flag1_u(tag, str, num);
	else
		no_flag_u(tag, str, num);
	free(str);
	return (0);
}
