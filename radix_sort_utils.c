/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 18:29:39 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Check for partial sorting during bit processing */
static int	check_partial_sorting(int last_val, int num, int *sorted_count)
{
	if (last_val != -1 && num > last_val)
		(*sorted_count)++;
	else
		*sorted_count = 0;
	return (num);
}

/* Process one bit of optimized radix sort */
void	process_bit_lsd(t_stack *stack_a, t_stack *stack_b,
							int bit, int size)
{
	int	j;
	int	num;
	int	last_val;
	int	sorted_count;

	j = 0;
	sorted_count = 0;
	last_val = -1;
	while (j < size && !is_sorted(stack_a))
	{
		num = stack_a->top->value;
		last_val = check_partial_sorting(last_val, num, &sorted_count);
		if ((num >> bit) & 1)
			ra(stack_a, 1);
		else
			pb(stack_a, stack_b);
		j++;
		if (sorted_count >= size / 3 && is_sorted(stack_a))
			break ;
	}
	if (is_sorted(stack_a) && stack_b->size == 0)
		return ;
	while (stack_b->size > 0)
		pa(stack_a, stack_b);
}

/* Sort very small stack efficiently with minimal operations */
void	sort_small_optimized(t_stack *stack_a, t_stack *stack_b)
{
	int	min;
	int	pos;
	int	counter;

	counter = 0;
	while (stack_a->size > 3 && !is_sorted(stack_a) && counter++ < 20)
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

/* Calculate optimal bit count for radix sort */
static int	calculate_max_bits(int size)
{
	int	max_bits;
	int	max_num;

	max_bits = 0;
	max_num = size - 1;
	while (max_num >> max_bits)
		max_bits++;
	return (max_bits);
}

/* Perform radix sort with early termination and optimizations */
void	perform_radix_sort(t_stack *stack_a, t_stack *stack_b, int size)
{
	int	max_bits;
	int	i;

	normalize_stack(stack_a);
	max_bits = calculate_max_bits(size);
	i = 0;
	while (i < max_bits && !is_sorted(stack_a))
	{
		process_bit_lsd(stack_a, stack_b, i, stack_a->size);
		if (is_sorted(stack_a))
			break ;
		i++;
	}
}
