/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 18:29:39 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Process one bit in optimized radix sort */
static void	process_bit_optimized(t_stack *stack_a, t_stack *stack_b,
								int num, int *stats)
{
	if ((num >> stats[0]) & 1)
	{
		ra(stack_a, 1);
		stats[1]++;
	}
	else
	{
		pb(stack_a, stack_b);
		stats[2] = 0;
		stats[3] = 0;
	}
}

/* Optimized radix sort with early termination */
void	do_radix_sort(t_stack *stack_a, t_stack *stack_b, int size, int bit)
{
	int	j;
	int	num;
	int	stats[4];

	j = 0;
	stats[0] = bit;
	stats[1] = 0;
	stats[2] = 1;
	stats[3] = 0;
	while (j < size && !is_sorted(stack_a))
	{
		num = stack_a->top->value;
		process_bit_optimized(stack_a, stack_b, num, stats);
		j++;
		stats[3]++;
		if (stats[1] > size / 2 && stats[2] && is_sorted(stack_a))
			break ;
	}
	while (stack_b->size > 0)
		pa(stack_a, stack_b);
}
