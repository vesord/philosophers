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

//static void	wait_permission(t_philosopher *volter)
//{
//	while (!volter->permission_to_eat)
//	{
//		if (!*volter->simulation)
//			break ;
//	}
//}

void		*philo_thread(void *arg)
{
	t_philosopher	*dekart;
	int				order;

	dekart = (t_philosopher*)arg;
//	dekart->is_ready += 1;
//	while (!*dekart->simulation)
//		;
	pthread_create(&dekart->thread_deathcheck_id, NULL, philo_deathcheck_thread, dekart);
	dekart->last_eat_time = get_timestamp();
	while (*dekart->simulation)
	{
		order = dekart->num % 2;
//		wait_permission(dekart);
		dekart->take_fork(dekart, order ? FORK_LEFT : FORK_RIGHT);
		dekart->say(dekart, SAY_TOOK_FORK);
		dekart->take_fork(dekart, order ? FORK_RIGHT : FORK_LEFT);
		dekart->say(dekart, SAY_TOOK_FORK);
		dekart->say(dekart, SAY_EAT);
		dekart->eat(dekart);
		dekart->drop_forks(dekart, order);
		dekart->say(dekart, SAY_SLEEP);
		dekart->sleep(dekart);
		dekart->say(dekart, SAY_THINK);
	}
	return ((void*)0);
}

void		*philo_deathcheck_thread(void *arg)
{
	t_philosopher	*sokrat;

	sokrat = (t_philosopher*)arg;
	pthread_detach(sokrat->thread_deathcheck_id);
//	sokrat->is_ready += 1;
//	while (!*sokrat->simulation)
//		;
//	usleep(1000);
	while(*sokrat->simulation)
	{
		pthread_mutex_lock(sokrat->eatdeath_mutex);
		if (get_timestamp() - sokrat->last_eat_time >= sokrat->time_to_die)
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
