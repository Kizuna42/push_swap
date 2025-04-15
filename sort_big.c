/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 18:10:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Process one chunk for large stacks */
void	process_large_chunk(t_stack *stack_a, t_stack *stack_b,
								int i, int chunk_size)
{
	int	j;
	int	size;

	j = 0;
	size = stack_a->size;
	while (j < size)
	{
		if (stack_a->top->value < (i + 1) * chunk_size)
		{
			pb(stack_a, stack_b);
			if (stack_b->top->value < i * chunk_size)
				rb(stack_b, 1);
		}
		else
			ra(stack_a, 1);
		j++;
	}
}

/* Advanced sorting algorithm for very large stacks (500+) */
void	optimized_large_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	size;
	int	chunk_count;
	int	chunk_size;
	int	i;

	normalize_stack(stack_a);
	size = stack_a->size;
	chunk_count = 11;
	chunk_size = size / chunk_count;
	i = 0;
	while (i < chunk_count - 1)
	{
		process_large_chunk(stack_a, stack_b, i, chunk_size);
		i++;
	}
	while (stack_a->size > 0)
		pb(stack_a, stack_b);
	while (stack_b->size > 0)
		pa(stack_a, stack_b);
}
