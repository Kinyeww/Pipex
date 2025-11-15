/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckin-yew <ckin-yew@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:23:51 by ckin-yew          #+#    #+#             */
/*   Updated: 2025/11/15 15:23:53 by ckin-yew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printhexa(unsigned int num, int upcase)
{
	char	*s;
	int		bytes;

	if (upcase == 0)
		s = "0123456789abcdef";
	else
		s = "0123456789ABCDEF";
	bytes = 0;
	if (num > 15)
		bytes += ft_printhexa(num / 16, upcase);
	write(1, &s[num % 16], 1);
	return (bytes + 1);
}

int	ft_putitoa(int n)
{
	int		i;
	char	*str;

	str = ft_itoa(n);
	i = ft_putstr(str);
	free(str);
	return (i);
}

int	ft_printpointer(void *ptr, int first)
{
	unsigned long	address;
	char			*s;
	int				bytes;

	address = (unsigned long)ptr;
	bytes = 0;
	if (address == 0)
		return (write(1, "(nil)", 5));
	if (first == 1)
	{
		bytes += 2;
		write(1, "0x", 2);
	}
	s = "0123456789abcdef";
	if (address > 15)
		bytes += ft_printpointer((void *)(address / 16), 0);
	write (1, &s[address % 16], 1);
	return (bytes + 1);
}

int	ft_checkformat(va_list args, const char **format)
{
	int	bytes;

	bytes = 0;
	(*format)++;
	if (**format == 'c')
		bytes += ft_putchar(va_arg(args, int));
	if (**format == 's')
		bytes += ft_putstr(va_arg(args, char *));
	if (**format == 'p')
		bytes += ft_printpointer(va_arg(args, void *), 1);
	if ((**format == 'd') || **format == 'i')
		bytes += ft_putitoa(va_arg(args, int));
	if (**format == 'u')
		bytes += ft_printunsigned(va_arg(args, unsigned int));
	if (**format == 'x')
		bytes += ft_printhexa(va_arg(args, unsigned int), 0);
	if (**format == 'X')
		bytes += ft_printhexa(va_arg(args, unsigned int), 1);
	if (**format == '%')
		bytes += write(1, "%", 1);
	return (bytes);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		bytes;

	va_start(args, format);
	bytes = 0;
	while (*format)
	{
		if (*format == '%')
			bytes += ft_checkformat(args, &format);
		else
			bytes += (ft_putchar(*format));
		format++;
	}
	va_end(args);
	return (bytes);
}
