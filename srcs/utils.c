/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:32:46 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/16 00:40:03 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

char	**ft_split_mult(char *str, char *delimiters)
{
	char	**result;
	char	*temp;
	int		i;

	temp = ft_strdup(str);
	if (!temp)
		return (NULL);
	i = 0;
	while (temp[i])
	{
		if (ft_strchr(delimiters, temp[i]))
			temp[i] = ' ';
		i++;
	}
	result = ft_split(temp, ' ');
	free(temp);
	return (result);
}

int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	get_start_stack(t_elem *stack)
{
	int	first;

	first = 0;
	while (stack[first].filled != 1)
		first++;
	if (stack[first].index == -1)
		first--;
	return (first);
}

int	get_end_stack(t_elem *stack)
{
	int	end;

	end = 0;
	while (stack[end].index != -1)
		end++;
	end--;
	return (end);
}

int	is_median(t_elem *stack, int num)
{
	int	start;
	int	end;
	int	higher;
	int	lower;

	start = get_start_stack(stack);
	end = get_end_stack(stack);
	higher = 0;
	lower = 0;
	while (start <= end)
	{
		if (stack[start].num > num)
			higher++;
		else if (stack[start].num < num)
			lower++;
		start++;
	}
	if ((higher - lower) >= -1 && (higher - lower) <= 1)
		return (1);
	return (0);
}
