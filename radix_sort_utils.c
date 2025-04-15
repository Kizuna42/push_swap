/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 19:03:22 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Process one bit of radix sort - optimized implementation */
void	process_bit_lsd(t_stack *stack_a, t_stack *stack_b,
							int bit, int size)
{
	int	i;
	int	num;
	int	mask;

	i = 0;
	mask = 1 << bit;
	while (i < size)
	{
		num = stack_a->top->value;
		if ((num & mask) == 0)
			pb(stack_a, stack_b);
		else
			ra(stack_a, 1);
		i++;
	}
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

	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	return (max_bits);
}

/* Check if stack is already sorted */
static int	check_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top || stack->size <= 1)
		return (1);
	current = stack->top;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

/* Perform radix sort with early termination and bit-mask optimization */
void	perform_radix_sort(t_stack *stack_a, t_stack *stack_b, int size)
{
	int	max_bits;
	int	i;

	if (is_sorted(stack_a))
		return ;
	normalize_stack(stack_a);
	if (check_sorted(stack_a))
		return ;
	max_bits = calculate_max_bits(size);
	i = 0;
	while (i < max_bits)
	{
		process_bit_lsd(stack_a, stack_b, i, size);
		if (is_sorted(stack_a))
			break ;
		i++;
	}
}
