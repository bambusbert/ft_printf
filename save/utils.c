/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:08:29 by slambert          #+#    #+#             */
/*   Updated: 2025/10/14 11:48:09 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(int n)
{
	long	nl;
	int		i;

	nl = n;
	i = 0;
	if (nl < 0)
	{
		i += ft_putchar_fd('-');
		nl *= -1;
	}
	if (nl > 9)
	{
		i += ft_putnbr_fd(nl / 10);
	}
	i += ft_putchar_fd(nl % 10 + '0');
	return (i);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	unsigned long	nl;
	int				i;

	nl = n;
	i = 0;
	if (nl < 0)
	{
		i += ft_putchar_fd('-');
		nl *= -1;
	}
	if (nl > 9)
	{
		i += ft_putnbr_fd(nl / 10);
	}
	i += ft_putchar_fd(nl % 10 + '0');
	return (i);
}

int	ft_putstr_fd(char *s)
{
	if (!s)
	{
		write (1, "(null)", 6);
		return (6);
	}
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	ft_putchar_fd(char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}