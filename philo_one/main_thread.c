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

	i = 0;
	while (++i < count)
	{
		status = pthread_mutex_unlock(party[i]->l_fork);
		if (status == 0)
			i++;
	}
	i = 0;
	while (i < count)
	{
		status = pthread_join(party[i]->thread_id, NULL);
		if (!status)
			i++;
	}
	// close mutexes and free here
	return (0);
}

static void	control_simulation(t_philosopher **party, t_args *arg, time_t *simulation)
{
	int i;
	int finished_eat;
	time_t	ts;

	while (*simulation)
	{
		finished_eat = 0;
		i = -1;
		while (*simulation && ++i < arg->philos)
		{
			ts = get_timestamp();
			if (ts - party[i]->last_eat_time  >= party[i]->time_to_die)
			{
				*simulation = 0;
				party[i]->say(party[i], SAY_DEAD, ts);
				party[i]->drop_forks(party[i], 1);
			}
			if (arg->eat_count && party[i]->count_eat >= arg->eat_count)
				finished_eat++;
		}
		if (finished_eat == arg->philos)
			*simulation = 0;
	}
}

extern time_t stamp[20];

int			main_thread(t_args *arg)
{
	t_philosopher	**party;
	time_t			simulation;
	int				i;


	party = NULL;
	if (!(party = initialization(arg, &simulation)))
		return (1);
	i = -1;
	simulation = 0;
	while (++i < arg->philos)
	{
		if (pthread_create(&party[i]->thread_id, NULL, philo_thread, party[i]))
			return (1);
	}

	i = 0;
	while (i < arg->philos)
		if (party[i]->last_eat_time)
			i++;


	simulation = 1;
	control_simulation(party, arg, &simulation);
	clear_restaurant(party, arg->philos);

	printf("\n\n");
	i = -1;
	while (++i < arg->philos)
	{
		printf("Philo %i has eaten %i times\n", party[i]->num, party[i]->count_eat);
	}

	printf("\n\n");
	i = -1;
	while (++i < arg->philos)
	{
		printf("Philo %i has timestamp %li times\n", party[i]->num, stamp[i]);
	}

	return (0);
}