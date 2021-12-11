/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:31:19 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 17:44:30 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct s_tag
{
	int		flag[2];
	int		field;
	int		prec;
	char	type;
	int		len;
	int		print_len;
	int		error;
}				t_tag;

int				ft_printf(const char *format, ...);
void			initialize_tags(t_tag *tag);
int				output_character(va_list *ap, t_tag *tag, char *format, int j);
int				prep_tags(va_list *ap, t_tag *tag, char *format, int i);
int				set_flag(t_tag *tag, char *format, int i);
int				set_field_prec(va_list *ap, t_tag *tag, char *format, int i);
int				has_asterisk(va_list *ap, t_tag *tag, int flag, int i);
int				no_asterisk(t_tag *tag, int flag, int i, char *format);
void			output_int(va_list *ap, t_tag *tag);
int				prep_len(t_tag tag, long d);
int				print_space(t_tag tag, int neg);
void			exist_flag0_u(t_tag *tag, long num, char *str, int neg);
void			exist_flag1(t_tag *tag, long d, int neg);
void			not_exist_flag(t_tag *tag, long d, int neg);
void			output_char(va_list *ap, t_tag *tag);
void			output_str(va_list *ap, t_tag *tag);
int				exist_flag0_str(t_tag tag, char *str);
int				check_precision(t_tag tag, char *str);
int				output_unsigned_int(va_list *ap, t_tag *tag);
int				check_ptr(va_list *ap, t_tag *tag, char **str);
unsigned int	set_len(va_list *ap, t_tag *tag, char **str);
void			exist_flag1_u(t_tag *tag, char *str, unsigned int num);
void			no_flag_u(t_tag *tag, char *str, unsigned int num);
int				print_unsigned_int(t_tag tag, long num, char *str);
int				convert_to_hex(unsigned int num, char **sum, t_tag tag);
int				convert_to_hex_ptr(uintptr_t num, char **sum);
void			concat_sum(char **sum, char *tmp);
void			ft_putchar(char c);
void			ft_putnum(long num);
void			ft_putstr_fd(char *s, int fd);
size_t			ft_strlen_NULL(const char *s);
char			*ft_strjoin_strict(char const *s1, char const *s2);

#	endif
