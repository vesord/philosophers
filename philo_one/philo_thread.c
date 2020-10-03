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
	useconds_t 		time;

	seneca = (t_philosopher*)arg;
	while (*seneca->simulation)
	{
		if ((time = get_timestamp()) - *seneca->simulation >= seneca->time_to_die)
		{
			*seneca->simulation = 0;
			seneca->say(seneca, SAY_DEAD, time);
		}
	}
	pthread_detach(seneca->thread_id);
	return (0);
}

void		*philo_thread(void *arg)
{
	t_philosopher *dekart;

	dekart = (t_philosopher*)arg;
	while (!*dekart->simulation)
		;
	if (pthread_create(&dekart->thread_id_die, NULL, time_to_death, NULL))
	{
		*dekart->simulation = 0;
		return ((void *)1);
	}
	while (*dekart->simulation)
	{
		dekart->take_fork(dekart, FORK_LEFT);
		dekart->say(dekart, SAY_TOOK_FORK, get_timestamp());
		dekart->take_fork(dekart, FORK_RIGHT);
		dekart->say(dekart, SAY_TOOK_FORK, get_timestamp());
		dekart->say(dekart, SAY_EAT, get_timestamp());
		dekart->eat(dekart);
		dekart->drop_forks(dekart);
		dekart->say(dekart, SAY_SLEEP, get_timestamp());
		dekart->sleep(dekart);
		dekart->say(dekart, SAY_THINK, get_timestamp());
	}
	dekart->drop_forks(dekart);
	return (0);
}
