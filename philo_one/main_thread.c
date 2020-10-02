/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:15:21 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 15:15:22 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

//
#include <stdio.h>

int		main_thread(t_args *arg)
{
	printf("philos: %i\n", arg->philos);
	printf("time to die: %i\n", arg->time_die);
	printf("time to eat: %i\n", arg->time_eat);
	printf("time to sleep: %i\n", arg->time_sleep);
	printf("eat count: %i\n", arg->eat_count);
	return (0);
}