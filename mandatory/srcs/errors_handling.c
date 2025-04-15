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

int	is_args_number(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (i < argc - 1)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				if (!(j == 0 && argv[i][j] == '-'))
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_duplicate_number(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 2)
	{
		if (ft_atoi(argv[0]) == 0 && ft_strncmp(argv[0], "0", 2) != 0)
			return (-1);
	}
	i = 0;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc - 1)
		{
			if ((ft_atoi(argv[i]) == 0 && ft_strncmp(argv[i], "0", 2) != 0)
				|| (ft_atoi(argv[j]) == 0 && ft_strncmp(argv[j], "0", 2) != 0))
				return (-1);
			if (ft_atoi(argv[i]) == ft_atoi(argv[j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_handle_errors(int argc, char **argv)
{
	if (argc == 1)
		return (0);
	if (is_args_number(argc, argv) == -1)
	{
		ft_putstr_fd("Error\n", 1);
		return (-1);
	}
	if (is_duplicate_number(argc, argv) == -1)
	{
		ft_putstr_fd("Error\n", 1);
		return (-1);
	}
	return (1);
}
