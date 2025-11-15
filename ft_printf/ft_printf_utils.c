/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckin-yew <ckin-yew@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:24:14 by ckin-yew          #+#    #+#             */
/*   Updated: 2025/11/15 15:24:15 by ckin-yew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
	return (i);
}

char	*ft_putnbr(char *str, long num, int len)
{
	str[len] = '\0';
	len--;
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	while (num > 0 && len >= 0)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;
	long	tmp;

	num = n;
	tmp = num;
	len = 0;
	if (tmp <= 0)
		len++;
	while (tmp != 0)
	{
		tmp /= 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (ft_putnbr(str, num, len));
}

int	ft_printunsigned(unsigned int nbr)
{
	char	*str;
	int		bytes;

	bytes = 0;
	str = "0123456789";
	if (nbr == 0)
		return (write(1, "4294967295", 10));
	if (nbr > 9)
		bytes += ft_printunsigned(nbr / 10);
	write(1, &str[nbr % 10], 1);
	return (bytes + 1);
}
