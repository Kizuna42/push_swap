/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:24:24 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 20:24:25 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	stack_init(t_stack *stack, t_stack *stack_b)
{
	stack->top = NULL;
	stack_b->top = NULL;
}

void	both_stack_index_init(t_stack *stack_a, t_stack *stack_b)
{
	stack_index_init(stack_a);
	stack_index_init(stack_b);
}

void	stack_index_init(t_stack *stack)
{
	t_node	*temp;
	int		index;

	temp = stack->top;
	index = 0;
	while (temp->next != stack->top)
	{
		temp->index = index;
		temp = temp->next;
		index++;
	}
	temp->index = index;
}

void	free_stack(t_stack *stack)
{
	t_node	*temp;
	t_node	*next;

	if (is_empty(stack))
		return ;
	temp = stack->top;
	while (temp->next != stack->top)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	free(temp);
	stack->top = NULL;
}
