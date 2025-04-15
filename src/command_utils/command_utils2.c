/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:22:47 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 20:55:12 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	command_set_rarb(t_command *command, int ra_count, int rb_count)
{
	int	with;

	with = 0;
	if (ra_count > rb_count)
		with = rb_count;
	else
		with = ra_count;
	command->ra = ra_count - with;
	command->rb = rb_count - with;
	command->rr = with;
	if (command->ra < 0 || command->rb < 0)
		command->all = 0;
	else
		command->all = command->ra + command->rb + command->rr;
}

void	command_set_rrarrb(t_command *command, int rra_count, int rrb_count)
{
	int	with;

	with = 0;
	if (ft_abs(rra_count) > ft_abs(rrb_count))
		with = ft_abs(rrb_count);
	else
		with = ft_abs(rra_count);
	command->rra = ft_abs(rra_count) - with;
	command->rrb = ft_abs(rrb_count) - with;
	command->rrr = with;
	if (command->rra < 0 || command->rrb < 0)
		command->all = 0;
	else
		command->all = command->rra + command->rrb + command->rrr;
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
