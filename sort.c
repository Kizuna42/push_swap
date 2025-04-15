/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:43:27 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Find the minimum value in the stack */
int	find_min(t_stack *stack)
{
	t_node	*current;
	int		min;

	if (!stack || !stack->top)
		return (0);
	current = stack->top;
	min = current->value;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

/* Find the position of a value in the stack */
int	find_position(t_stack *stack, int value)
{
	t_node	*current;
	int		pos;

	if (!stack || !stack->top)
		return (-1);
	current = stack->top;
	pos = 0;
	while (current)
	{
		if (current->value == value)
			return (pos);
		current = current->next;
		pos++;
	}
	return (-1);
}

/* Handle sort cases for three elements */
static void	sort_three_cases(t_stack *stack_a, int first, int second, int third)
{
	if (first > second && second < third && first < third)
		sa(stack_a, 1);
	else if (first > second && second > third)
	{
		sa(stack_a, 1);
		rra(stack_a, 1);
	}
	else if (first > second && second < third && first > third)
		ra(stack_a, 1);
	else if (first < second && second > third && first < third)
	{
		sa(stack_a, 1);
		ra(stack_a, 1);
	}
	else if (first < second && second > third && first > third)
		rra(stack_a, 1);
}

/* Sort a stack with only 3 elements */
void	sort_three(t_stack *stack_a)
{
	int	first;
	int	second;
	int	third;

	if (!stack_a || !stack_a->top || !stack_a->top->next
		|| !stack_a->top->next->next || stack_a->size > 3)
		return ;
	first = stack_a->top->value;
	second = stack_a->top->next->value;
	third = stack_a->top->next->next->value;
	sort_three_cases(stack_a, first, second, third);
}
