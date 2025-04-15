/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 19:28:22 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Find the position of the maximum value in the stack */
int	find_max_position(t_stack *stack)
{
	t_node	*current;
	int		max;
	int		pos;
	int		max_pos;

	if (!stack || !stack->top)
		return (-1);
	current = stack->top;
	max = current->value;
	pos = 0;
	max_pos = 0;
	while (current)
	{
		if (current->value > max)
		{
			max = current->value;
			max_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (max_pos);
}

/* Process one chunk of numbers for optimized sorting */
static void	process_one_chunk(t_stack *stack_a, t_stack *stack_b,
				int current_chunk, int *pushed)
{
	int	j;
	int	chunk_size;

	j = 0;
	chunk_size = current_chunk / 10 + 1;
	while (j < stack_a->size * 2 && *pushed < current_chunk + chunk_size
		&& stack_a->size > 0)
	{
		if (stack_a->top->value >= current_chunk
			&& stack_a->top->value < current_chunk + chunk_size)
		{
			pb(stack_a, stack_b);
			(*pushed)++;
		}
		else
			ra(stack_a, 1);
		j++;
	}
}

/* Push chunks of numbers to stack_b in an optimized order */
void	push_chunks(t_stack *stack_a, t_stack *stack_b, int chunks,
		int chunk_size)
{
	int	i;
	int	pushed;
	int	current_chunk;

	i = 0;
	pushed = 0;
	while (i < chunks && stack_a->size > 0)
	{
		current_chunk = i * chunk_size;
		process_one_chunk(stack_a, stack_b, current_chunk, &pushed);
		i++;
	}
}

/* Push all maximum values from stack_b back to stack_a in descending order */
void	push_max_to_a(t_stack *stack_a, t_stack *stack_b)
{
	int	max_pos;
	int	size;

	while (stack_b->size > 0)
	{
		max_pos = find_max_position(stack_b);
		size = stack_b->size;
		if (max_pos <= size / 2)
		{
			while (max_pos > 0)
			{
				rb(stack_b, 1);
				max_pos--;
			}
		}
		else
		{
			while (max_pos < size)
			{
				rrb(stack_b, 1);
				max_pos++;
			}
		}
		pa(stack_a, stack_b);
	}
}

/* Main function to sort large stacks of numbers (>250) */
void	sort_large(t_stack *stack_a, t_stack *stack_b)
{
	int	size;

	if (!stack_a || !stack_b || is_sorted(stack_a))
		return ;
	normalize_stack(stack_a);
	size = stack_a->size;
	if (size <= 0)
		return ;
	optimized_large_sort(stack_a, stack_b);
}
