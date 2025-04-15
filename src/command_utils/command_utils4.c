/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:26:53 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 20:54:51 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	calculate_rotate_count(int index, int len)
{
	if (index <= len / 2)
		return (index);
	return (index - len);
}

static int	get_with_value(int a_count, int b_count, int mode)
{
	int	with;

	if (mode == RA_RB)
	{
		if (a_count > b_count)
			with = b_count;
		else
			with = a_count;
	}
	else
	{
		if (ft_abs(a_count) > ft_abs(b_count))
			with = ft_abs(b_count);
		else
			with = ft_abs(a_count);
	}
	return (with);
}

int	calculate_min_command(int a_count, int b_count, int mode)
{
	int	with;

	if ((a_count > 0 && b_count > 0 && mode == RA_RB)
		|| (a_count < 0 && b_count < 0 && mode == RRA_RRB))
	{
		with = get_with_value(a_count, b_count, mode);
		return (with + ft_abs(a_count - b_count));
	}
	return (ft_abs(a_count) + ft_abs(b_count));
}

void	set_command_based_on_mode(t_command *command, int ra_count,
							int rb_count, int min_mode)
{
	if (min_mode == RA_RB)
		command_set_rarb(command, ra_count, rb_count);
	else if (min_mode == RRA_RRB)
		command_set_rrarrb(command, ra_count, rb_count);
	else if (min_mode == RA_RRB)
		command_set_rarrb(command, ra_count, rb_count);
	else
		command_set_rrarb(command, ra_count, rb_count);
}

int	get_min_mode(int ra_count, int rb_count)
{
	int	min_mode;
	int	min;
	int	temp;

	min_mode = RA_RB;
	min = calculate_min_command(ra_count, rb_count, RA_RB);
	temp = calculate_min_command(ra_count, -rb_count, RA_RRB);
	if (min > temp)
	{
		min = temp;
		min_mode = RA_RRB;
	}
	temp = calculate_min_command(-ra_count, rb_count, RRA_RB);
	if (min > temp)
	{
		min = temp;
		min_mode = RRA_RB;
	}
	temp = calculate_min_command(-ra_count, -rb_count, RRA_RRB);
	if (min > temp)
		min_mode = RRA_RRB;
	return (min_mode);
}

t_command	calculation_command(int a_index, int b_index, int a_len, int b_len)
{
	t_command	command;
	int			ra_count;
	int			rb_count;
	int			min_mode;

	command = command_init();
	ra_count = calculate_rotate_count(a_index, a_len);
	rb_count = calculate_rotate_count(b_index, b_len);
	min_mode = get_min_mode(ra_count, rb_count);
	set_command_based_on_mode(&command, ra_count, rb_count, min_mode);
	return (command);
}
