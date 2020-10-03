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

int			clear_restaurant(t_philosopher **party, int count)
{
	int	i;
	int	join_status;
	int status;

	i = 0;
	join_status = 0;
	while (i < count)
	{
		write(1, "|", 1);
		printf("joining i = %i ", i);
		status = pthread_join(party[i]->thread_id, NULL);
		printf("status %i\n", status);
		i++;
	}
	// close mutexes and free here
	return (0);
}

int			main_thread(t_args *arg)
{
	t_philosopher	**party;
	time_t			simulation;
	int				i;

	simulation = 0;
	party = NULL;
	if (!(party = initialization(arg, &simulation)))
		return (1);
	i = -1;
	while (++i < arg->philos)
		if (pthread_create(&(party[i]->thread_id), NULL, philo_thread, party[i])
		|| pthread_create(&(party[i]->thread_id_die), NULL, time_to_death, party[i]))
			return (1);

	simulation = get_timestamp();

	while (simulation)
		;
	return (clear_restaurant(party, arg->philos));
	return (0);
}