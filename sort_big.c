/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 19:05:25 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Process one chunk for large stacks with presorting */
void	process_large_chunk(t_stack *stack_a, t_stack *stack_b,
								int i, int chunk_size)
{
	int	j;
	int	size;
	int	quarter;

	j = 0;
	size = stack_a->size;
	quarter = chunk_size / 4;
	while (j < size && !is_sorted(stack_a))
	{
		if (stack_a->top->value < (i + 1) * chunk_size)
		{
			pb(stack_a, stack_b);
			if (stack_b->size > 1)
			{
				if (stack_b->top->value < i * chunk_size + quarter)
					rb(stack_b, 1);
				else if (stack_b->top->value < i * chunk_size + 2 * quarter
					&& stack_b->size > 2)
					rb(stack_b, 1);
			}
		}
		else
			ra(stack_a, 1);
		j++;
	}
}

/* Optimized large sorting with dynamic chunk count */
void	optimized_large_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	size;
	int	chunk_count;
	int	chunk_size;
	int	i;

	normalize_stack(stack_a);
	size = stack_a->size;
	if (size <= 500)
		chunk_count = 9;
	else
		chunk_count = 11 + (size / 100);
	chunk_size = size / chunk_count + (size % chunk_count != 0);
	i = 0;
	while (i < chunk_count - 1 && !is_sorted(stack_a))
	{
		process_large_chunk(stack_a, stack_b, i, chunk_size);
		i++;
	}
	if (!is_sorted(stack_a))
	{
		while (stack_a->size > 0)
			pb(stack_a, stack_b);
		push_max_to_a(stack_a, stack_b);
	}
}
