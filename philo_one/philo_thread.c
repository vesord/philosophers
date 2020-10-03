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
	while (!*seneca->simulation)
		;
	seneca->last_eat_time = *seneca->simulation;
	while (*seneca->simulation)
	{
		if (get_timestamp() - seneca->last_eat_time  >= seneca->time_to_die)
		{
			*seneca->simulation = 0;
			seneca->say(seneca, SAY_DEAD, get_timestamp());
			seneca->drop_forks(seneca);
			write(1, "i dropped forks!\n", 17);
		}
	}
	//pthread_detach(seneca->thread_id_die);
	return (0);
}

void		*philo_thread(void *arg)
{
	t_philosopher	*dekart;

	dekart = (t_philosopher*)arg;
	while (!*dekart->simulation)
		;
//	if (dekart->num == 2)
//		write(1, "2 started!\n", 11);
	write(1, (dekart->num == 2) ? "!!!2!!!" : "!!!1!!!", 7);
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
	if (dekart->num == 2)
		write(1, "2 about to drop!\n", 17);
	dekart->drop_forks(dekart);
	pthread_join(dekart->thread_id_die, NULL);
	return (0);
}
