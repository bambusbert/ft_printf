/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:38:27 by slambert          #+#    #+#             */
/*   Updated: 2025/10/14 13:43:43 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	dispatcher(va_list ap, char c);
int	pointer_handler(va_list ap);

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*p;
	int		i;
	int		ret;

	va_start(ap, fmt);
	p = (char *)fmt;
	i = 0;
	ret = 0;
	while (p[i++])
	{
		if (p[i - 1] != '%')
			ret += ft_putchar_fd(p[i - 1]);
		else
		{
			ret += dispatcher(ap, p[i]);
			i++;
		}
	}
	va_end(ap);
	return (ret);
}

int	dispatcher(va_list ap, char c)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(ap, int)));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(ap, char *)));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr_fd(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(ap, int)));
	else if (c == 'p')
		return (pointer_handler(ap));
	else if (c == 'X')
		return (ft_putnbr_hex(va_arg(ap, int)));
	else if (c == 'x')
		return (ft_putnbr_hex_lowercase(va_arg(ap, int)));
	else if (c == '%')
		return (ft_putchar_fd('%'));
	else
	{
		ft_putchar_fd('%');
		ft_putchar_fd(c);
		return (2);
	}
}

int	pointer_handler(va_list ap)
{
	unsigned long	pointer_value;

	pointer_value = va_arg(ap, unsigned long);
	if (pointer_value == 0)
	{
		ft_putstr_fd("(nil)");
		return (5);
	}
	else
	{
		ft_putstr_fd("0x");
		return (ft_putnbr_hex_pointer(pointer_value) + 2);
	}
}

/* 
int	main(void)
{
	const char	*p = "%d%d%d";
	char str[] = "fbnshbvqe";

	// printf("arguments: %d\n", count_args(p));
	// ft_printf("asd%ifg%ih", 5, 4);
	// ft_printf("%i%c%i%i%i\n", 1, 'd', 2, 3, 4);
	// printf("%p\n", p);
	// ft_printf("%p\n", p);
	// printf("OG %s\n", str);
	// ft_printf("MY %s\n", str);

	// printf("OG %d\n", -10);
	// ft_printf("MY %d\n", -10);

	// printf("OG %p\n", p);
	// ft_printf("MY %p\n", p);

	// ft_putnbr_hex(123456);
	// printf("\n");
	// ft_putnbr_hex_lowercase(123456);

	// printf("OG %X\n", 1234);
	// ft_printf("MY %X\n", 1234);

	// printf("OG %k\n", 1234);
	// ft_printf("MY %k\n", 1234);

	// int x;
	// x = printf("OG: %d\n", 12345);
	// printf("return (value of OG: %d\n", x));
	// x = ft_printf("MY: %d\n", 12345);
	// printf("return (value of MY: %d\n", x));

	// printf("OG %x\n", 255);
	// ft_printf("MY %x\n", 255);

	// printf("OG %p\n", NULL);
	// ft_printf("MY %p\n", NULL);

	printf("OG: Pointer: %p\n", &str);
	ft_printf("MY: Pointer: %p\n", &str);

	// printf("OG: HEX: %X\n", &str);
	// ft_printf("MY: HEX: %X\n", &str);

	printf("OG: %x\n", 0);
	ft_printf("MY: %x\n", 0);
} */
