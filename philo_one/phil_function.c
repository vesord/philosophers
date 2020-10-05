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

void	phil_eat(t_philosopher *self, time_t ts)
{
	if (!*self->simulation)
		return ;
	self->last_eat_time = ts;
	if (self->count_eat > 0)
		self->count_eat--;
	usleep(self->time_eat);
}

void	phil_sleep(t_philosopher *self)
{
	if (!*self->simulation)
		return ;
	usleep(self->time_sleep);
}

void	phil_say(t_philosopher *self, enum e_phrases what, time_t ts)
{
	int						say_str_len;
	char					*say_str;
	static int				is_last_msg;

	if (!*self->simulation && what != SAY_DEAD)
		return ;
	say_str_len = 35 + ft_ilen(self->num);
	if (!(say_str = (char*)malloc(sizeof(char) * say_str_len)))
		return ;
	memset(say_str, '\0', say_str_len);
	form_say_string(say_str, ts / 1000, self->num, g_phrases[what]);
	pthread_mutex_lock(self->say_mutex);
	if (!*self->simulation && is_last_msg)
		return ;
	if (what == SAY_DEAD)
		is_last_msg = !is_last_msg;
	write(1, say_str, ft_strlen(say_str));
	pthread_mutex_unlock(self->say_mutex);
	free(say_str);
}

void	phil_take_fork(t_philosopher *self, enum e_forks frk)
{
	if (!*self->simulation)
		return ;
	if (frk == FORK_LEFT)
	{
//		while (officiant < 2)
//			;
		pthread_mutex_lock(self->l_fork);
		officiant--;
		if (!*self->simulation)
			pthread_mutex_unlock(self->l_fork);
	}
	else if (frk == FORK_RIGHT)
	{
		pthread_mutex_lock(self->r_fork);
		officiant--;
		if (!*self->simulation)
			pthread_mutex_unlock(self->r_fork);
	}
}

void	phil_drop_forks(t_philosopher *self)
{
	if (!(self->num % 2))
	{
		pthread_mutex_unlock(self->r_fork);
		pthread_mutex_unlock(self->l_fork);
	}
	else
	{
		pthread_mutex_unlock(self->l_fork);
		pthread_mutex_unlock(self->r_fork);
	}
	officiant += 2;
}