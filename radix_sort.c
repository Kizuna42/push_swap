/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 18:10:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Execute one pass of radix sort (for compatibility) */
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
