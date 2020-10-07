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

extern time_t		g_cur_time;

void		*philo_thread(void *arg)
{
	t_philosopher	*dekart;
	int				order;

	dekart = (t_philosopher*)arg;
	pthread_create(&dekart->thread_deathcheck_id, NULL, philo_deathcheck_thread,
																		dekart);
	dekart->is_ready++;
	while (!*dekart->simulation)
		;
	dekart->last_eat_time = 0;
	pthread_mutex_unlock(dekart->eatdeath_mutex);
	while (*dekart->simulation)
	{
		order = dekart->num % 2;
		phil_take_fork(dekart, order ? FORK_LEFT : FORK_RIGHT);
		phil_say(dekart, SAY_TOOK_FORK);
		phil_take_fork(dekart, order ? FORK_RIGHT : FORK_LEFT);
		phil_say(dekart, SAY_TOOK_FORK);
		phil_say(dekart, SAY_EAT);
		phil_eat(dekart);
		phil_drop_forks(dekart, order);
		phil_say(dekart, SAY_SLEEP);
		phil_sleep(dekart);
		phil_say(dekart, SAY_THINK);
	}
	pthread_mutex_unlock(dekart->eatdeath_mutex);
	pthread_join(dekart->thread_deathcheck_id, NULL);
	return ((void*)0);
}

void		*philo_deathcheck_thread(void *arg)
{
	t_philosopher	*sokrat;

	sokrat = (t_philosopher*)arg;
	sokrat->is_ready++;
	while (!*sokrat->simulation)
		;
	while (*sokrat->simulation)
	{
		pthread_mutex_lock(sokrat->eatdeath_mutex);
		if (g_cur_time - sokrat->last_eat_time >= sokrat->time_to_die)
		{
			*sokrat->simulation = 0;
			sokrat->say(sokrat, SAY_DEAD);
			sokrat->drop_forks(sokrat, 1);
		}
		pthread_mutex_unlock(sokrat->eatdeath_mutex);
		usleep(1000);
	}
	return ((void*)0);
}
