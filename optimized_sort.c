/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 18:25:07 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Push chunks to stack_b based on dynamic value ranges */
void	push_chunks(t_stack *stack_a, t_stack *stack_b, int chunks,
						int chunk_size)
{
	int	i;
	int	j;
	int	half_size;

	i = 0;
	half_size = chunk_size / 2;
	while (i < chunks && !is_sorted(stack_a))
	{
		j = 0;
		while (j < chunk_size && !is_sorted(stack_a))
		{
			if (stack_a->top->value < (i + 1) * chunk_size)
			{
				pb(stack_a, stack_b);
				if (stack_b->top->value < i * chunk_size + half_size
					&& stack_b->size > 1)
					rb(stack_b, 1);
				j++;
			}
			else
				ra(stack_a, 1);
		}
		i++;
	}
}

/* Extract maximum value from stack_b with optimized search */
int	find_max_position(t_stack *stack_b)
{
	t_node	*current;
	int		max_pos;
	int		max_val;
	int		i;

	if (!stack_b || !stack_b->top)
		return (-1);
	max_pos = 0;
	max_val = stack_b->top->value;
	current = stack_b->top->next;
	i = 1;
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

/* Optimized push maximum value with rotation optimization */
void	push_max_to_a(t_stack *stack_a, t_stack *stack_b)
{
	int		max_pos;
	int		size_b;

	while (stack_b->size > 0)
	{
		max_pos = find_max_position(stack_b);
		size_b = stack_b->size;
		if (max_pos == 0)
			pa(stack_a, stack_b);
		else if (max_pos <= size_b / 2)
		{
			while (max_pos-- > 0)
				rb(stack_b, 1);
			pa(stack_a, stack_b);
		}
		else
		{
			while (max_pos++ < size_b)
				rrb(stack_b, 1);
			pa(stack_a, stack_b);
		}
	}
}

/* Sort medium size stacks with dynamic chunking */
static void	sort_medium(t_stack *stack_a, t_stack *stack_b, int chunks)
{
	int	size;
	int	chunk_size;

	normalize_stack(stack_a);
	size = stack_a->size;
	chunk_size = size / chunks + (size % chunks != 0);
	push_chunks(stack_a, stack_b, chunks, chunk_size);
	if (!is_sorted(stack_a))
	{
		while (stack_a->size > 0)
			pb(stack_a, stack_b);
		push_max_to_a(stack_a, stack_b);
	}
}

/* Advanced adaptive sort algorithm selector */
void	sort_large(t_stack *stack_a, t_stack *stack_b)
{
	int	size;

	if (is_sorted(stack_a))
		return ;
	size = stack_a->size;
	if (size <= 5)
		sort_small(stack_a, stack_b);
	else if (size <= 30)
		sort_small_optimized(stack_a, stack_b);
	else if (size <= 100)
		sort_medium(stack_a, stack_b, 5);
	else if (size <= 300)
		sort_medium(stack_a, stack_b, 8);
	else
		optimized_large_sort(stack_a, stack_b);
}
