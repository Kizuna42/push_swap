/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:22:53 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 20:30:21 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_command	command_init(void)
{
	t_command	command;

	command.all = 0;
	command.ra = 0;
	command.rra = 0;
	command.rb = 0;
	command.rrb = 0;
	command.rr = 0;
	command.rrr = 0;
	return (command);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	calculate_rotate_count(int index, int len)
{
	if (index <= len / 2)
		return (index);
	return (index - len);
}

static int	calculate_min_command(int a_count, int b_count, int mode)
{
	int	with;

	if ((a_count > 0 && b_count > 0 && mode == RA_RB)
		|| (a_count < 0 && b_count < 0 && mode == RRA_RRB))
	{
		if (mode == RA_RB)
			with = (a_count > b_count) ? b_count : a_count;
		else
			with = (ft_abs(a_count) > ft_abs(b_count))
				? ft_abs(b_count) : ft_abs(a_count);
		return (with + ft_abs(a_count - b_count));
	}
	return (ft_abs(a_count) + ft_abs(b_count));
}

t_command	calculation_command(int a_index, int b_index, int a_len, int b_len)
{
	t_command	command;
	int			ra_count;
	int			rb_count;
	int			min_mode;
	int			min;

	command = command_init();
	ra_count = calculate_rotate_count(a_index, a_len);
	rb_count = calculate_rotate_count(b_index, b_len);
	min_mode = RA_RB;
	min = calculate_min_command(ra_count, rb_count, RA_RB);
	if (min > calculate_min_command(ra_count, -rb_count, RA_RRB))
	{
		min = calculate_min_command(ra_count, -rb_count, RA_RRB);
		min_mode = RA_RRB;
	}
	if (min > calculate_min_command(-ra_count, rb_count, RRA_RB))
	{
		min = calculate_min_command(-ra_count, rb_count, RRA_RB);
		min_mode = RRA_RB;
	}
	if (min > calculate_min_command(-ra_count, -rb_count, RRA_RRB))
		min_mode = RRA_RRB;
	if (min_mode == RA_RB)
		commnad_set_rarb(&command, ra_count, rb_count);
	else if (min_mode == RRA_RRB)
		commnad_set_rrarrb(&command, ra_count, rb_count);
	else if (min_mode == RA_RRB)
		command_set_rarrb(&command, ra_count, rb_count);
	else
		command_set_rrarb(&command, ra_count, rb_count);
	return (command);
}

void	do_command(t_command command, t_stack *stack_a, t_stack *stack_b)
{
	while (command.rr-- > 0)
		rr(stack_a, stack_b);
	while (command.ra-- > 0)
		ra(stack_a);
	while (command.rb-- > 0)
		rb(stack_b);
	while (command.rrr-- > 0)
		rrr(stack_a, stack_b);
	while (command.rra-- > 0)
		rra(stack_a);
	while (command.rrb-- > 0)
		rrb(stack_b);
}
