/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:40:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* sa: swap the first 2 elements at the top of stack a */
void	sa(t_stack *stack_a, int print)
{
	t_node	*first;
	t_node	*second;

	if (!stack_a || !stack_a->top || !stack_a->top->next)
		return ;
	first = stack_a->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	stack_a->top = second;
	if (print)
		write(1, "sa\n", 3);
}

/* sb: swap the first 2 elements at the top of stack b */
void	sb(t_stack *stack_b, int print)
{
	t_node	*first;
	t_node	*second;

	if (!stack_b || !stack_b->top || !stack_b->top->next)
		return ;
	first = stack_b->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	stack_b->top = second;
	if (print)
		write(1, "sb\n", 3);
}

/* ss: sa and sb at the same time */
void	ss(t_stack *stack_a, t_stack *stack_b)
{
	sa(stack_a, 0);
	sb(stack_b, 0);
	write(1, "ss\n", 3);
}

/* pa: take the first element at the top of b and put it at the top of a */
void	pa(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*temp;

	if (!stack_b || !stack_b->top)
		return ;
	temp = stack_b->top;
	stack_b->top = temp->next;
	temp->next = stack_a->top;
	stack_a->top = temp;
	stack_a->size++;
	stack_b->size--;
	write(1, "pa\n", 3);
}

/* pb: take the first element at the top of a and put it at the top of b */
void	pb(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*temp;

	if (!stack_a || !stack_a->top)
		return ;
	temp = stack_a->top;
	stack_a->top = temp->next;
	temp->next = stack_b->top;
	stack_b->top = temp;
	stack_b->size++;
	stack_a->size--;
	write(1, "pb\n", 3);
}
