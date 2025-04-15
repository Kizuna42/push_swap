/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:44:21 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Execute one pass of radix sort */
void	do_radix_sort(t_stack *stack_a, t_stack *stack_b, int size, int bit)
{
	int	j;
	int	num;

	j = 0;
	while (j < size)
	{
		num = stack_a->top->value;
		if ((num >> bit) & 1)
			ra(stack_a, 1);
		else
			pb(stack_a, stack_b);
		j++;
	}
	while (stack_b->size > 0)
		pa(stack_a, stack_b);
}

/* Sort small stack (up to 5 elements) */
void	sort_small(t_stack *stack_a, t_stack *stack_b)
{
	int	min;
	int	pos;

	if (!stack_a || !stack_b || stack_a->size <= 3)
		return ;
	while (stack_a->size > 3)
	{
		min = find_min(stack_a);
		pos = find_position(stack_a, min);
		while (stack_a->top->value != min)
		{
			if (pos <= stack_a->size / 2)
				ra(stack_a, 1);
			else
				rra(stack_a, 1);
		}
		pb(stack_a, stack_b);
	}
	sort_three(stack_a);
	while (stack_b->size > 0)
		pa(stack_a, stack_b);
}

/* Sort large stack using radix sort */
void	sort_large(t_stack *stack_a, t_stack *stack_b)
{
	int	max_bits;
	int	i;
	int	size;

	max_bits = 0;
	size = stack_a->size;
	while ((size - 1) >> max_bits)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		do_radix_sort(stack_a, stack_b, size, i);
		i++;
	}
}

/* Main sorting function - decides which sort algorithm to use */
void	sort_stack(t_stack *stack_a, t_stack *stack_b)
{
	if (!stack_a || !stack_b || is_sorted(stack_a))
		return ;
	if (stack_a->size == 2)
		sa(stack_a, 1);
	else if (stack_a->size == 3)
		sort_three(stack_a);
	else if (stack_a->size <= 5)
		sort_small(stack_a, stack_b);
	else
		sort_large(stack_a, stack_b);
}
