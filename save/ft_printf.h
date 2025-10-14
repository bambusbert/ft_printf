/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slambert <slambert@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:38:59 by slambert          #+#    #+#             */
/*   Updated: 2025/10/14 11:31:57 by slambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

size_t	ft_strlen(const char *str);
int	ft_putchar_fd(char c);
int	ft_putnbr_fd(int n);
int	ft_putstr_fd(char *s);
//for testing remove later!
int	ft_printf(const char *fmt, ...);

#endif