/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:36:27 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 18:36:29 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static t_philosopher	*philosopher_init(t_args *arg, int i,
					pthread_mutex_t *mutexes, time_t *simulation)
{
	t_philosopher *kant;

	if (!(kant = (t_philosopher*)malloc(sizeof(t_philosopher))))
		return (NULL);
	kant->num = i + 1;
	kant->simulation = simulation;
	kant->last_eat_time = 0;
	kant->time_eat = arg->time_eat * 1000;
	kant->time_sleep = arg->time_sleep * 1000;
	kant->time_to_die = arg->time_die * 1000;
	kant->count_eat = 0;
	kant->eat = phil_eat;
	kant->sleep = phil_sleep;
	kant->say = phil_say;
	kant->take_fork = phil_take_fork;
	kant->drop_forks = phil_drop_forks;
	kant->l_fork = &(mutexes[i]);
	if (i + 1 == arg->philos)
		kant->r_fork = &(mutexes[0]);
	else
		kant->r_fork = &(mutexes[i + 1]);
	kant->say_mutex = &(mutexes[arg->philos]);
	return (kant);
}

static int	phil_mutex_init(pthread_mutex_t *mutexes, int mutexes_count)
{
	int i;

	i = -1;
	while (++i < mutexes_count)
		if (pthread_mutex_init(&mutexes[i], NULL))
			return (1);
	return (0);
}

static int	party_init(t_philosopher **party, t_args *arg, time_t *simulation)
{
	pthread_mutex_t	*mutexes;
	int				i;

	if (!(mutexes = (pthread_mutex_t*)malloc(
		sizeof(pthread_mutex_t) * (arg->philos + 1))))
		return (1);
	if (phil_mutex_init(mutexes, arg->philos + 1))
		return (1);
	i = -1;
	while (++i < arg->philos)
		if (!(party[i] = philosopher_init(arg, i, mutexes, simulation)))
			return (1);
	return (0);
}

t_philosopher	**initialization(t_args *arg, time_t *simulation)
{
	t_philosopher **party;

	if (!(party = (t_philosopher**)malloc(sizeof(t_philosopher*) * arg->philos)))
		return (NULL);
	if (party_init(party, arg, simulation))
		return (NULL);
	return (party);
}