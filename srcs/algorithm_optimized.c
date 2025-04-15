/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_optimized.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:32:28 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/16 00:41:32 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	process_chunk(t_elem *stack_a, t_elem *stack_b, int chunk_idx,
						int chunk_size)
{
	int	j;
	int	min_idx;

	j = 0;
	while (j < chunk_size && get_start_stack(stack_a) <= get_end_stack(stack_a))
	{
		min_idx = get_start_stack(stack_a);
		if (stack_a[min_idx].num <= (chunk_idx + 1) * chunk_size
			&& stack_a[min_idx].num > chunk_idx * chunk_size)
		{
			push_stack(stack_a, stack_b, "pb\n");
			if (stack_b[get_start_stack(stack_b)].num
				<= (chunk_idx + 0.5) * chunk_size)
				shift_up(stack_b, "rb\n");
			j++;
		}
		else
			shift_up(stack_a, "ra\n");
	}
}

void	move_to_b(t_elem *stack_a, t_elem *stack_b, int stack_size)
{
	int	i;
	int	size;
	int	chunk_size;
	int	chunk_count;

	size = stack_size - 1;
	chunk_count = 5;
	if (stack_size > 250)
		chunk_count = 11;
	chunk_size = size / chunk_count;
	i = 0;
	while (i < chunk_count)
	{
		process_chunk(stack_a, stack_b, i, chunk_size);
		i++;
	}
	while (get_start_stack(stack_a) <= get_end_stack(stack_a))
		push_stack(stack_a, stack_b, "pb\n");
}

void	move_max_to_top(t_elem *stack_b, int max_idx)
{
	int	i;
	int	min_idx;

	min_idx = get_start_stack(stack_b);
	i = min_idx;
	if (max_idx - min_idx < get_end_stack(stack_b) - max_idx + 1)
	{
		while (i < max_idx)
		{
			shift_up(stack_b, "rb\n");
			i++;
		}
	}
	else
	{
		while (max_idx < get_end_stack(stack_b) + 1)
		{
			shift_down(stack_b, "rrb\n");
			max_idx++;
		}
	}
}

void	move_back_to_a(t_elem *stack_a, t_elem *stack_b)
{
	int	max_idx;

	while (get_start_stack(stack_b) <= get_end_stack(stack_b))
	{
		max_idx = get_max_stack(stack_b, -1).index;
		move_max_to_top(stack_b, max_idx);
		push_stack(stack_b, stack_a, "pa\n");
	}
}

void	resolve_stack(t_elem *stack_a, t_elem *stack_b, int stack_size)
{
	if (stack_size <= 5)
	{
		if (stack_size <= 3)
			resolve_three(stack_a);
		else
			small_sort(stack_a, stack_b, stack_size);
		return ;
	}
	move_to_b(stack_a, stack_b, stack_size);
	move_back_to_a(stack_a, stack_b);
}
