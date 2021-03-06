/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:31:24 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 14:31:35 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
		write(2, "Error. Something in threading went wrong. :(\n", 45);
		return (1);
	}
	return (0);
}

void	print_help(void)
{
	write(1, "\nUSAGE\n", 7);
	write(1, "./philo_one number_of_philosophers ", 35);
	write(1, "time_to_die time_to_eat time_to_sleep ", 38);
	write(1, "[number_of_times_each_philosopher_must_eat]\n", 44);
}
