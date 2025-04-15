/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 18:02:15 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Compare function for qsort */
static int	compare_ints(const void *a, const void *b)
{
	int	val_a;
	int	val_b;

	val_a = *((int *)a);
	val_b = *((int *)b);
	return (val_a - val_b);
}

/* Find index of value in sorted array using binary search */
static int	binary_search(int *arr, int left, int right, int x)
{
	int	mid;

	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (arr[mid] == x)
			return (mid);
		if (arr[mid] < x)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}

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

/* Update stack values with their sorted indices */
static void	update_stack_values(t_stack *stack,
	int *orig, int *sorted, int size)
{
	t_node	*current;
	int		i;

	current = stack->top;
	i = 0;
	while (current)
	{
		current->value = binary_search(sorted, 0, size - 1, orig[i]);
		current = current->next;
		i++;
	}
}

/* Convert stack values to indices for more efficient sorting */
void	normalize_stack(t_stack *stack)
{
	int		*original;
	int		*sorted;
	int		size;

	size = stack->size;
	original = (int *)malloc(sizeof(int) * size);
	sorted = (int *)malloc(sizeof(int) * size);
	if (!original || !sorted)
	{
		if (original)
			free(original);
		if (sorted)
			free(sorted);
		return ;
	}
	fill_arrays(stack, original, sorted);
	qsort(sorted, size, sizeof(int), compare_ints);
	update_stack_values(stack, original, sorted, size);
	free(original);
	free(sorted);
}
