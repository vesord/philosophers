/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 17:25:48 by matrus            #+#    #+#             */
/*   Updated: 2020/10/03 17:48:21 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*time_to_death(void *arg)
{
	t_philosopher	*seneca;

	seneca = (t_philosopher*)arg;
	while (*seneca->simulation)
	{
		if (seneca->last_eat_time - *seneca->simulation >= seneca->time_to_die)
		{
			*seneca->simulation = 0;
			seneca->say(seneca, SAY_DEAD, get_timestamp());
		}
	}
	pthread_detach(seneca->thread_id);
	return (0);
}

static int	timer_to_death_create(t_philosopher *platon)
{
	if (pthread_create(&platon->thread_id_die, NULL, time_to_death, NULL))
	{
		*platon->simulation = 0;
		return (1);
	}
	return (0);
}

void		*philo_thread(void *arg)
{
	t_philosopher	*dekart;

	dekart = (t_philosopher*)arg;
	while (!*dekart->simulation)
		;
	if (timer_to_death_create(dekart))
		return ((void *)1);
	while (*dekart->simulation)
	{
		dekart->take_fork(dekart, FORK_LEFT);
		dekart->say(dekart, SAY_TOOK_FORK, get_timestamp());
		dekart->take_fork(dekart, FORK_RIGHT);
		dekart->say(dekart, SAY_TOOK_FORK, get_timestamp());
		dekart->say(dekart, SAY_EAT, get_timestamp());
		dekart->eat(dekart, get_timestamp());
		dekart->drop_forks(dekart);
		dekart->say(dekart, SAY_SLEEP, get_timestamp());
		dekart->sleep(dekart);
		dekart->say(dekart, SAY_THINK, get_timestamp());
	}
	dekart->drop_forks(dekart);
	return (0);
}
