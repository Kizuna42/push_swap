/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:24:15 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 20:24:16 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

bool	is_sorted(t_stack *stack)
{
	t_node	*temp;

	temp = stack->top;
	while (temp->next != stack->top)
	{
		if (temp->data > temp->next->data)
			return (false);
		temp = temp->next;
	}
	return (true);
}

bool	is_empty(t_stack *stack)
{
	return (stack->top == NULL);
}
