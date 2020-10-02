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
					pthread_mutex_t *mutexes, suseconds_t *simulation)
{
	t_philosopher *kant;

	if (!(kant = (t_philosopher*)malloc(sizeof(t_philosopher))))
		return (NULL);
	kant->num = i + 1;
	kant->simulation = simulation;
	kant->last_eat_time = 0;
	kant->is_dead = 0;
	kant->time_eat = arg->time_eat;
	kant->time_sleep = arg->time_sleep;
	kant->count_eat = arg->eat_count;
	kant->eat = phil_eat;
	kant->sleep = phil_sleep;
	kant->say = phil_say;
	kant->l_fork = &mutexes[i];
	kant->r_fork = &mutexes[i + 1];
	return (kant);
}

static int	party_init(t_philosopher **party, t_args *arg,
					suseconds_t *simulation)
{
	pthread_mutex_t	*mutexes;
	int				i;

	if (!(mutexes = (pthread_mutex_t*)malloc(
		sizeof(pthread_mutex_t) * (arg->philos + 1))))
		return (1);
	i = -1;
	while (++i < arg->philos)
		if (pthread_mutex_init(&mutexes[i], NULL))
			return (1);
	mutexes[i] = mutexes[0];
	i = -1;
	while (++i < arg->philos)
		if (!(party[i] = philosopher_init(arg, i, mutexes, simulation)))
			return (1);
	return (0);
}

//static int	phil_function_init()
//{
//	phil_eat(NULL);
//	phil_say(NULL, NULL, 0);
//	phil_sleep(NULL);
//	return (0);
//}

int	initialization(t_philosopher **party, t_args *arg, suseconds_t *simulation)
{
	if (!(party = (t_philosopher**)malloc(sizeof(t_philosopher*) * arg->philos)))
		return (1);
	if (party_init(party, arg, simulation))
		return (1);
//	if (phil_function_init())
//		return (1);
	return (0);
}