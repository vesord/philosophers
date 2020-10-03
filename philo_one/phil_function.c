/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:46:40 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 18:46:42 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	phil_eat(t_philosopher *self)
{
	if (!*self->simulation)
		return ;
	usleep(self->time_eat);
}

void	phil_sleep(t_philosopher *self)
{
	if (!*self->simulation)
		return ;
	usleep(self->time_sleep);
}

void	phil_say(t_philosopher *self, enum e_phrases what, suseconds_t ts)
{
	if (!*self->simulation && what != SAY_DEAD)
		return ;
	write(1, "say smth!\n", 10);
}

void	phil_take_fork(t_philosopher *self, enum e_forks frk)
{
	if (!*self->simulation)
		return ;
	if (frk == FORK_LEFT)
		pthread_mutex_lock(self->l_fork);
	else if (frk == FORK_RIGHT)
		pthread_mutex_lock(self->r_fork);
}

void	phil_drop_forks(t_philosopher *self)
{
	pthread_mutex_unlock(self->l_fork);
	pthread_mutex_unlock(self->r_fork);
}