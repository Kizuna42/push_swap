/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:22:53 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 20:43:08 by kizuna           ###   ########.fr       */
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
