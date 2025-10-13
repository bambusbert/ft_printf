/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:38:27 by slambert          #+#    #+#             */
/*   Updated: 2025/10/13 18:24:36 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dispatcher(va_list ap, char c);
void	ft_putnbr_hex(int num);
void	ft_putnbr_hex_lowercase(int num);

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*p;
	int		i;

	va_start(ap, fmt);
	p = (char *)fmt;
	i = 0;
	while (p[i++])
	{
		if (p[i - 1] != '%')
			ft_putchar_fd(p[i - 1], 1);
		else
		{
			dispatcher(ap, p[i]);
			i++;
		}
	}
	va_end(ap);
	return (0);
}

void	dispatcher(va_list ap, char c)
{
	if (c == 'c')
		ft_putchar_fd(va_arg(ap, int), 1);
	if (c == 's')
		ft_putstr_fd(va_arg(ap, char*), 1);
	if (c == 'i' || c == 'd' || c == 'u')	//this OK? original prints garbage, but should be undefined?
		ft_putnbr_fd(va_arg(ap, int), 1);
	if (c == 'p' || c == 'X')
	{
		ft_putstr_fd("0x", 1);
		ft_putnbr_hex(va_arg(ap, int));
	}
	if (c == 'x')
	{
		ft_putstr_fd("0x", 1);
		ft_putnbr_hex_lowercase(va_arg(ap, int));
	}
	if (c == '%')
		ft_putchar_fd('%', 1);
	//let it crash on purpose?? bc not a valid character
	
}

void	ft_putnbr_hex(int num)
{
	long	n;

	n = (long)num;
	// maybe remove negative handling because undefined?
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n *= -1;
	}
	if (n > 15)
		ft_putnbr_hex(n / 16);
	if ((n % 16) < 10)
		ft_putchar_fd(n % 16 + 48, 1);
	else
		ft_putchar_fd(n % 16 + 55, 1);
}

void	ft_putnbr_hex_lowercase(int num)
{
	long	n;

	n = (long)num;
	// maybe remove negative handling because undefined?
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n *= -1;
	}
	if (n > 15)
		ft_putnbr_hex(n / 16);
	if ((n % 16) < 10)
		ft_putchar_fd(n % 16 + 48, 1);
	else
		ft_putchar_fd(n % 16 + 87, 1);
}

int	main(void)
{
	const char	*p = "%d%d%d";
	char str[] = "fbnshbvqe";

	// printf("arguments: %d\n", count_args(p));
	// ft_printf("asd%ifg%ih", 5, 4);
	// ft_printf("%i%c%i%i%i\n", 1, 'd', 2, 3, 4);
	printf("%p\n", p);
	ft_printf("%p\n", p);
	// printf("OG %s\n", str);
	// ft_printf("MY %s\n", str);
	
	// printf("OG %d\n", -10);
	// ft_printf("MY %d\n", -10);

	printf("OG %p\n", p);
	ft_printf("MY %p\n", p);
	
	ft_putnbr_hex(123456);
	printf("\n");
	ft_putnbr_hex_lowercase(123456);
}
