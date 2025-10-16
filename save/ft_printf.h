/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:38:59 by slambert          #+#    #+#             */
/*   Updated: 2025/10/14 12:04:12 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int	ft_printf(const char *fmt, ...);
int	ft_putnbr_fd(int n);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_putstr_fd(char *s);
int	ft_putchar_fd(char c);
size_t	ft_strlen(const char *str);
int	ft_putnbr_hex(unsigned int num);
int	ft_putnbr_hex_lowercase(unsigned int num);
int	ft_putnbr_hex_pointer(unsigned long num);

//for testing remove later!
//int	ft_printf(const char *fmt, ...);

#endif