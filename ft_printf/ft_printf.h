/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckin-yew <ckin-yew@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:24:27 by ckin-yew          #+#    #+#             */
/*   Updated: 2025/11/15 15:24:29 by ckin-yew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int		ft_putchar(int c);
int		ft_strlen(char *str);
int		ft_putstr(char *s);
int		ft_printhexa(unsigned int num, int upcase);
int		ft_checkformat(va_list args, const char **format);
int		ft_printf(const char *format, ...);
int		ft_printpointer(void *ptr, int first);
int		ft_putitoa(int n);
char	*ft_itoa(int n);
char	*ft_putnbr(char *str, long num, int len);
int		ft_printunsigned(unsigned int nbr);
