/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:40:56 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* rra: shift down all elements of stack a by 1, last becomes first */
void	rra(t_stack *stack_a, int print)
{
	t_node	*prev;
	t_node	*last;

	if (!stack_a || !stack_a->top || !stack_a->top->next)
		return ;
	prev = NULL;
	last = stack_a->top;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = stack_a->top;
	stack_a->top = last;
	if (print)
		write(1, "rra\n", 4);
}

/* rrb: shift down all elements of stack b by 1, last becomes first */
void	rrb(t_stack *stack_b, int print)
{
	t_node	*prev;
	t_node	*last;

	if (!stack_b || !stack_b->top || !stack_b->top->next)
		return ;
	prev = NULL;
	last = stack_b->top;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = stack_b->top;
	stack_b->top = last;
	if (print)
		write(1, "rrb\n", 4);
}

/* rrr: rra and rrb at the same time */
void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	rra(stack_a, 0);
	rrb(stack_b, 0);
	write(1, "rrr\n", 4);
}
