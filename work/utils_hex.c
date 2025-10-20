/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:48:30 by slambert          #+#    #+#             */
/*   Updated: 2025/10/17 19:13:41 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(unsigned int num)
{
	long	n;
	int		ret;

	n = (long)num;
	ret = 0;
	if (n > 15)
	{
		ret += ft_putnbr_hex(n / 16);
	}

	
	if ((n % 16) < 10)
		ret += ft_putchar_fd(n % 16 + '0');
	else
		ret += ft_putchar_fd(n % 16 + 55);
	return (ret);
}

int	ft_putnbr_hex_lowercase(unsigned int num)
{
	long	n;
	int		ret;

	n = (long)num;
	ret = 0;
	if (n > 15)
		ret += ft_putnbr_hex_lowercase(n / 16);
	if ((n % 16) < 10)
		ret += ft_putchar_fd(n % 16 + 48);
	else
		ret += ft_putchar_fd(n % 16 + 87);
	return (ret);
}

int	ft_putnbr_hex_pointer(unsigned long num)
{
	int	ret;

	ret = 0;
	if (num > 15)
		ret += ft_putnbr_hex_pointer(num / 16);
	if ((num % 16) < 10)
		ret += ft_putchar_fd(num % 16 + 48);
	else
		ret += ft_putchar_fd(num % 16 + 87);
	return (ret);
}
