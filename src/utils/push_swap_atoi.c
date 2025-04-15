/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:24:35 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 20:43:51 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <ctype.h>

static int	check_overflow(long value, int sign, char next_digit)
{
	long	next_value;

	next_value = value * 10 + (next_digit - '0');
	if (sign > 0 && next_value > 2147483647)
		return (1);
	if (sign < 0 && - next_value < -2147483648)
		return (1);
	return (0);
}

static bool	process_digits(char *str, long *value, int sign, int *num)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		if (check_overflow(*value, sign, *str))
			return (false);
		*value = *value * 10 + (*str - '0');
		str++;
	}
	*num = (int)(*value * sign);
	return (true);
}

bool	push_swap_atoi(char *str, int *num)
{
	long	value;
	int		sign;

	value = 0;
	while (isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str == '\0')
		return (false);
	return (process_digits(str, &value, sign, num));
}
