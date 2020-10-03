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

const char	*g_phrases[] =
	{
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

void phil_eat(t_philosopher *self, useconds_t ts)
{
	if (!*self->simulation)
		return ;
	self->last_eat_time = ts;
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
	static pthread_mutex_t	write_mutex;
	static int				is_mutex_inited;

	if (!*self->simulation && what != SAY_DEAD)
		return ;
	if (!is_mutex_inited)
	{
		if (pthread_mutex_init(&write_mutex, NULL))
			*self->simulation = 0;
		is_mutex_inited++;
	}
	pthread_mutex_lock(&write_mutex);
	ft_putunbr(ts);
	write(1, " ", 1);
	ft_putunbr(self->num);
	write(1, " ", 1);
	ft_putstrln(g_phrases[what]);
	pthread_mutex_unlock(&write_mutex);
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