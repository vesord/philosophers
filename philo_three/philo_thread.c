/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 17:25:48 by matrus            #+#    #+#             */
/*   Updated: 2020/10/09 11:43:59 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	actions(t_philosopher *kopernic)
{
	sem_wait(kopernic->servant_sem);
	kopernic->take_fork(kopernic);
	kopernic->say(kopernic, SAY_TOOK_FORK);
	kopernic->take_fork(kopernic);
	kopernic->say(kopernic, SAY_TOOK_FORK);
	kopernic->say(kopernic, SAY_EAT);
	kopernic->eat(kopernic);
	kopernic->drop_forks(kopernic);
	sem_post(kopernic->servant_sem);
	kopernic->say(kopernic, SAY_SLEEP);
	kopernic->sleep(kopernic);
	kopernic->say(kopernic, SAY_THINK);
}

void		philo_process(void *arg)
{
	t_philosopher	*dekart;

	dekart = (t_philosopher*)arg;
	if (pthread_create(&dekart->deathcheck_id, NULL, deathcheck_thread, dekart))
	{
		write(2, "FATAL: can not thread inside process. Exiting...\n", 49);
		sem_post(dekart->simulation_sem);
		exit(1);
	}
	while (!*dekart->simulation)
		;
	dekart->last_eat_time = get_timestamp();
	sem_post(dekart->eatdeath_sem);
	while (*dekart->simulation)
	{
		actions(dekart);
	}
	sem_post(dekart->eatdeath_sem);
	pthread_join(dekart->deathcheck_id, NULL);
	while (1)
		;
}

void		*deathcheck_thread(void *arg)
{
	t_philosopher	*sokrat;

	sokrat = (t_philosopher*)arg;
	*sokrat->simulation = get_timestamp();
	while (*sokrat->simulation)
	{
		sem_wait(sokrat->eatdeath_sem);
		if (!*sokrat->simulation)
			break ;
		if (get_timestamp() - sokrat->last_eat_time >= sokrat->time_to_die)
		{
			*sokrat->simulation = 0;
			sokrat->say(sokrat, SAY_DEAD);
			sem_post(sokrat->simulation_sem);
			sokrat->drop_forks(sokrat);
		}
		sem_post(sokrat->eatdeath_sem);
		usleep(1000);
	}
	return ((void*)0);
}
