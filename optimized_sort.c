/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 18:09:32 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Push chunks to stack_b based on value ranges */
void	push_chunks(t_stack *stack_a, t_stack *stack_b, int chunks,
						int chunk_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < chunks && !is_sorted(stack_a))
	{
		j = 0;
		while (j < chunk_size && !is_sorted(stack_a))
		{
			if (stack_a->top->value < (i + 1) * chunk_size
				&& stack_a->top->value >= i * chunk_size)
			{
				pb(stack_a, stack_b);
				j++;
			}
			else
				ra(stack_a, 1);
		}
		i++;
	}
}

/* Extract maximum value from stack_b */
int	find_max_position(t_stack *stack_b)
{
	t_node	*current;
	int		max_pos;
	int		max_val;
	int		i;

	max_pos = 0;
	max_val = -1;
	current = stack_b->top;
	i = 0;
	while (current)
	{
		if (current->value > max_val)
		{
			max_val = current->value;
			max_pos = i;
		}
		current = current->next;
		i++;
	}
	return (max_pos);
}

/* Push max value and prepare it for push */
void	push_max_to_a(t_stack *stack_a, t_stack *stack_b)
{
	int		max_pos;
	int		max_val;
	t_node	*current;
	int		i;

	while (stack_b->size > 0)
	{
		max_pos = find_max_position(stack_b);
		current = stack_b->top;
		i = 0;
		while (i < max_pos)
		{
			current = current->next;
			i++;
		}
		max_val = current->value;
		if (max_pos <= stack_b->size / 2)
			while (stack_b->top->value != max_val)
				rb(stack_b, 1);
		else
			while (stack_b->top->value != max_val)
				rrb(stack_b, 1);
		pa(stack_a, stack_b);
	}
}

/* Chunking sort and main sort selector */
void	sort_large(t_stack *stack_a, t_stack *stack_b)
{
	int	size;
	int	chunks;
	int	chunk_size;

	if (is_sorted(stack_a))
		return ;
	size = stack_a->size;
	if (size <= 5)
		sort_small(stack_a, stack_b);
	else if (size <= 30)
		sort_small_optimized(stack_a, stack_b);
	else if (size <= 200)
	{
		normalize_stack(stack_a);
		chunks = 5;
		chunk_size = size / chunks;
		push_chunks(stack_a, stack_b, chunks, chunk_size);
		if (is_sorted(stack_a) && stack_b->size == 0)
			return ;
		while (stack_a->size > 0 && !is_sorted(stack_a))
			pb(stack_a, stack_b);
		push_max_to_a(stack_a, stack_b);
	}
	else
		optimized_large_sort(stack_a, stack_b);
}
