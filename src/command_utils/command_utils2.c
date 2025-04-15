/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:22:47 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 20:30:50 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	commnad_set_rarb(t_command *command, int ra_count, int rb_count)
{
	command->ra = 0;
	command->rb = 0;
	command->rra = 0;
	command->rrb = 0;
	command->rrr = 0;
	command->rr = 0;
	command->all = 0;
	if (ra_count > 0)
		command->ra = ra_count;
	if (rb_count > 0)
		command->rb = rb_count;
	if (ra_count > 0 && rb_count > 0)
	{
		command->rr = get_min(ra_count, rb_count);
		command->ra -= command->rr;
		command->rb -= command->rr;
		command->all = command->rr + ft_abs(ra_count - rb_count);
	}
	else
		command->all = command->ra + command->rb;
}

void	commnad_set_rrarrb(t_command *command, int rra_count, int rrb_count)
{
	command->ra = 0;
	command->rb = 0;
	command->rra = 0;
	command->rrb = 0;
	command->rrr = 0;
	command->rr = 0;
	command->all = 0;
	if (rra_count < 0)
		command->rra = ft_abs(rra_count);
	if (rrb_count < 0)
		command->rrb = ft_abs(rrb_count);
	if (rrb_count < 0 && rra_count < 0)
	{
		command->rrr = get_min(command->rra, command->rrb);
		command->rra -= command->rrr;
		command->rrb -= command->rrr;
		command->all = command->rrr + ft_abs(rra_count - rrb_count);
	}
	else
		command->all = command->rra + command->rrb;
}

void	command_set_rarrb(t_command *command, int ra_count, int rrb_count)
{
	command->ra = ra_count;
	command->rb = 0;
	command->rra = 0;
	command->rrb = rrb_count;
	command->rr = 0;
	command->rrr = 0;
	command->all = ra_count + rrb_count;
}

void	command_set_rrarb(t_command *command, int rra_count, int rb_count)
{
	command->ra = 0;
	command->rb = rb_count;
	command->rra = rra_count;
	command->rrb = 0;
	command->rr = 0;
	command->rrr = 0;
	command->all = rra_count + rb_count;
}
