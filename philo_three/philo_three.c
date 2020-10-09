/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:31:24 by matrus            #+#    #+#             */
/*   Updated: 2020/10/09 11:43:41 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		main(int argc, char **argv)
{
	t_args	arg;

	memset(&arg, 0, sizeof(t_args));
	if (argc < 5 || argc > 6)
	{
		write(2, "Error. Wrong arguments.\n", 24);
		print_help();
		return (1);
	}
	else if (set_arg(&arg, argc, argv))
	{
		write(2, "Error. Wrong arguments.\n", 24);
		print_help();
		return (1);
	}
	else if (arg.eat_count != 0 && main_thread(&arg))
	{
		write(2, "Error. Something in forking went wrong. :(\n", 45);
		return (1);
	}
	return (0);
}

void	print_help(void)
{
	write(1, "\nUSAGE\n", 7);
	write(1, "./philo_three number_of_philosophers ", 37);
	write(1, "time_to_die time_to_eat time_to_sleep ", 38);
	write(1, "[number_of_times_each_philosopher_must_eat]\n", 44);
}
