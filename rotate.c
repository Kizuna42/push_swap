/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:45:38 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ra: shift up all elements of stack a by 1, first becomes last */
void	ra(t_stack *stack_a, int print)
{
	t_node	*first;
	t_node	*last;

	if (!stack_a || !stack_a->top || !stack_a->top->next)
		return ;
	first = stack_a->top;
	stack_a->top = first->next;
	last = stack_a->top;
	while (last->next)
		last = last->next;
	last->next = first;
	first->next = NULL;
	if (print)
		write(1, "ra\n", 3);
}

/* rb: shift up all elements of stack b by 1, first becomes last */
void	rb(t_stack *stack_b, int print)
{
	t_node	*first;
	t_node	*last;

	if (!stack_b || !stack_b->top || !stack_b->top->next)
		return ;
	first = stack_b->top;
	stack_b->top = first->next;
	last = stack_b->top;
	while (last->next)
		last = last->next;
	last->next = first;
	first->next = NULL;
	if (print)
		write(1, "rb\n", 3);
}

/* rr: ra and rb at the same time */
void	rr(t_stack *stack_a, t_stack *stack_b)
{
	ra(stack_a, 0);
	rb(stack_b, 0);
	write(1, "rr\n", 3);
}
