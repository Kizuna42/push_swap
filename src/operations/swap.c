/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:24:07 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 20:24:08 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_stack *stack, char c)
{
	t_node	*first;
	t_node	*second;
	int		temp;

	if (is_empty(stack) || stack->top->next == stack->top)
		return ;
	first = stack->top;
	second = first->next;
	temp = first->data;
	first->data = second->data;
	second->data = temp;
	ft_printf("s%c\n", c);
}

void	sa(t_stack *stack_a)
{
	swap(stack_a, 'a');
}

void	sb(t_stack *stack_b)
{
	swap(stack_b, 'b');
}

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	swap(stack_a, 'a');
	swap(stack_b, 'b');
}
