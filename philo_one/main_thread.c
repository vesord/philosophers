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
	int status;

	i = -1;
	while (++i < count)
		pthread_mutex_unlock(party[i]->l_fork);
	i = 0;
	while (i < count)
	{
//		printf("thread %2i id: %li\n", i, (long)party[i]->thread_id);
		status = pthread_join(party[i]->thread_id, NULL);
		if (!status)
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
	i = 0;
	while (i < arg->philos)
		if (party[i]->is_philo_ready == 2)
		{
//			printf("thread %2i id: %li\n", i, (long)party[i]->thread_id);
			i++;
		}
	simulation = get_timestamp();

	i = 0;
	while (simulation)
		if (i < arg->philos && party[i]->count_eat == 0)
			i++;
		else
			if (i == arg->philos)
				simulation = 0;
	clear_restaurant(party, arg->philos);
	return (0);
}