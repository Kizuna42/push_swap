/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:48:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/16 01:48:01 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	print_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (-1);
}

int	ps_parse_int(const char *str, int *out)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	num = 0;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		if (num * sign > INT_MAX || num * sign < INT_MIN)
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	*out = (int)(num * sign);
	return (1);
}

int	ft_handle_errors(int argc, char **argv)
{
	int	i;
	int	j;
	int	num;
	int	other;

	if (argc == 1)
		return (0);
	i = 0;
	while (i < argc - 1)
	{
		if (!ps_parse_int(argv[i], &num))
			return (print_error());
		j = 0;
		while (j < i)
		{
			ps_parse_int(argv[j], &other);
			if (num == other)
				return (print_error());
			j++;
		}
		i++;
	}
	return (1);
}
