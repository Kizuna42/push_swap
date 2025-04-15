/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 18:04:06 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Process one bit of optimized radix sort */
void	process_bit_lsd(t_stack *stack_a, t_stack *stack_b,
							int bit, int size)
{
	int	j;
	int	num;

	j = 0;
	while (j < size && !is_sorted(stack_a))
	{
		num = stack_a->top->value;
		if ((num >> bit) & 1)
			ra(stack_a, 1);
		else
			pb(stack_a, stack_b);
		j++;
	}
	if (is_sorted(stack_a) && stack_b->size == 0)
		return ;
	while (stack_b->size > 0)
		pa(stack_a, stack_b);
}

/* Sort very small stack efficiently */
void	sort_small_optimized(t_stack *stack_a, t_stack *stack_b)
{
	int	min;
	int	pos;

	while (stack_a->size > 3 && !is_sorted(stack_a))
	{
		min = find_min(stack_a);
		pos = find_position(stack_a, min);
		if (pos <= stack_a->size / 2)
		{
			while (stack_a->top->value != min)
				ra(stack_a, 1);
		}
		else
		{
			while (stack_a->top->value != min)
				rra(stack_a, 1);
		}
		pb(stack_a, stack_b);
	}
	if (!is_sorted(stack_a))
		sort_three(stack_a);
	while (stack_b->size > 0)
		pa(stack_a, stack_b);
}

/* Perform radix sort with early termination on sorted condition */
void	perform_radix_sort(t_stack *stack_a, t_stack *stack_b, int size)
{
	int	max_bits;
	int	i;

	normalize_stack(stack_a);
	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	i = 0;
	while (i < max_bits && !is_sorted(stack_a))
	{
		process_bit_lsd(stack_a, stack_b, i, stack_a->size);
		if (is_sorted(stack_a))
			break ;
		i++;
	}
}
