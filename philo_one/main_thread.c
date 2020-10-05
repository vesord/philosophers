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
				party[i]->is_dead = 0;
				party[i]->say(party[i], SAY_DEAD, ts);
				party[i]->drop_forks(party[i]);
			}
			if (party[i]->count_eat == 0)
				finished_eat++;
		}
	}
}

int			main_thread(t_args *arg)
{
	t_philosopher	**party;
	time_t			simulation;
	int				i;


	party = NULL;
	if (!(party = initialization(arg, &simulation)))
		return (1);
	i = -1;
	simulation = 1;
	while (++i < arg->philos)
	{
		party[i]->last_eat_time = get_timestamp();
		if (pthread_create(&party[i]->thread_id, NULL, philo_thread, party[i]))
			return (1);
	}
	control_simulation(party, arg, &simulation);
	clear_restaurant(party, arg->philos);
	return (0);
}