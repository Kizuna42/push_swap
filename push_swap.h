/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:43:27 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

/* Main functions */
int		main(int argc, char **argv);

/* Stack operations */
t_stack	*init_stack(void);
void	free_stack(t_stack *stack);
void	push(t_stack *stack, int value);
int		pop(t_stack *stack);
void	print_stack(t_stack *stack);

/* Push_swap operations */
void	sa(t_stack *stack_a, int print);
void	sb(t_stack *stack_b, int print);
void	ss(t_stack *stack_a, t_stack *stack_b);
void	pa(t_stack *stack_a, t_stack *stack_b);
void	pb(t_stack *stack_a, t_stack *stack_b);
void	ra(t_stack *stack_a, int print);
void	rb(t_stack *stack_b, int print);
void	rr(t_stack *stack_a, t_stack *stack_b);
void	rra(t_stack *stack_a, int print);
void	rrb(t_stack *stack_b, int print);
void	rrr(t_stack *stack_a, t_stack *stack_b);

/* Sort algorithms */
void	sort_stack(t_stack *stack_a, t_stack *stack_b);
void	sort_three(t_stack *stack_a);
void	sort_small(t_stack *stack_a, t_stack *stack_b);
void	sort_large(t_stack *stack_a, t_stack *stack_b);

/* Sort utils */
int		find_min(t_stack *stack);
int		find_position(t_stack *stack, int value);
void	do_radix_sort(t_stack *stack_a, t_stack *stack_b, int size, int bit);

/* Utilities */
int		ft_atoi(const char *str);
int		is_sorted(t_stack *stack);
void	error_exit(void);
int		has_duplicates(int *array, int size);
int		is_valid_int(char *str);

#endif
