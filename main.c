/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:45:02 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Validate and convert arguments */
static int	*validate_args(int argc, char **argv)
{
	int	i;
	int	*nums;

	nums = (int *)malloc(sizeof(int) * (argc - 1));
	if (!nums)
		error_exit();
	i = 1;
	while (i < argc)
	{
		if (!is_valid_int(argv[i]))
		{
			free(nums);
			error_exit();
		}
		nums[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	if (has_duplicates(nums, argc - 1))
	{
		free(nums);
		error_exit();
	}
	return (nums);
}

/* Process arguments and fill stack */
static void	process_args(int argc, char **argv, t_stack *stack_a)
{
	int	i;
	int	*nums;

	nums = validate_args(argc, argv);
	i = argc - 1;
	while (i > 0)
		push(stack_a, nums[--i]);
	free(nums);
}

/* Initialize stacks and clean up resources */
static void	cleanup(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a)
		free_stack(stack_a);
	if (stack_b)
		free_stack(stack_b);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = init_stack();
	stack_b = init_stack();
	if (!stack_a || !stack_b)
	{
		cleanup(stack_a, stack_b);
		error_exit();
	}
	process_args(argc, argv, stack_a);
	if (!is_sorted(stack_a))
		sort_stack(stack_a, stack_b);
	cleanup(stack_a, stack_b);
	return (0);
}
