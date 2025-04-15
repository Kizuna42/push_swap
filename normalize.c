/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 19:02:15 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Fill original array with values from stack */
static void	fill_arrays(t_stack *stack, int *orig, int *sorted)
{
	t_node	*current;
	int		i;

	current = stack->top;
	i = 0;
	while (current)
	{
		orig[i] = current->value;
		sorted[i] = current->value;
		current = current->next;
		i++;
	}
}

/* Create an array of indices for original array values */
static void	create_index_map(int *sorted, int *index_map, int size)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (i < size)
	{
		count = 0;
		j = 0;
		while (j < size)
		{
			if (sorted[i] > sorted[j])
				count++;
			j++;
		}
		index_map[i] = count;
		i++;
	}
}

/* Update stack values with their sorted indices */
static void	update_stack_values(t_stack *stack, int *orig,
	int *index_map, int size)
{
	t_node	*current;
	int		j;

	current = stack->top;
	while (current)
	{
		j = 0;
		while (j < size)
		{
			if (orig[j] == current->value)
			{
				current->value = index_map[j];
				break ;
			}
			j++;
		}
		current = current->next;
	}
}

/* Convert stack values to indices for more efficient sorting */
void	normalize_stack(t_stack *stack)
{
	int		*original;
	int		*sorted;
	int		*index_map;
	int		size;

	size = stack->size;
	original = (int *)malloc(sizeof(int) * size);
	sorted = (int *)malloc(sizeof(int) * size);
	index_map = (int *)malloc(sizeof(int) * size);
	if (!original || !sorted || !index_map)
	{
		if (original)
			free(original);
		if (sorted)
			free(sorted);
		if (index_map)
			free(index_map);
		return ;
	}
	fill_arrays(stack, original, sorted);
	create_index_map(original, index_map, size);
	update_stack_values(stack, original, index_map, size);
	free(original);
	free(sorted);
	free(index_map);
}
