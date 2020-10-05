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

//
#include <stdio.h>

void	*time_to_death(void *arg)
{
	t_philosopher	*seneca;

	seneca = (t_philosopher*)arg;
	seneca->is_philo_ready++;
	while (!*seneca->simulation)
	{
//		;
		usleep(1000 * 100);
		printf("%i waiting dead\n", seneca->num);
		write(1, "wait to die\n", 12);
	}
	seneca->last_eat_time = *seneca->simulation;
	while (*seneca->simulation)
	{
		if (get_timestamp() - seneca->last_eat_time  >= seneca->time_to_die)
		{
			*seneca->simulation = 0;
			seneca->say(seneca, SAY_DEAD, get_timestamp());
			seneca->is_dead = 1;
			seneca->drop_forks(seneca);
		}
	}
	return (0);
}



void		*philo_thread(void *arg)
{
	t_philosopher	*dekart;

	dekart = (t_philosopher*)arg;
	dekart->is_philo_ready++;
	while (!*dekart->simulation && !dekart->is_dead)
	{
//		;
		usleep(1000 * 100);
		printf("%i waiting\n", dekart->num);
		write(1, "wait\n", 5);
	}
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
	pthread_join(dekart->thread_id_die, NULL);
	return (0);
}
