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

typedef struct	s_to_say
{
	char			*say_str;
	int				say_str_len;
	pthread_mutex_t	*say_mutex;
	enum e_phrases	what;
	time_t			*simulation;
	pthread_t		say_thread_id;
}				t_to_say;

void	*say_thread(void *arg)
{
	static int	is_last_msg;
	t_to_say	*to_say;

	to_say = (t_to_say*)arg;

	pthread_mutex_lock(to_say->say_mutex);
	if (!*to_say->simulation && is_last_msg)
		return (0);
	if (to_say->what == SAY_DEAD)
		is_last_msg = !is_last_msg;
	write(1, to_say->say_str, ft_strlen(to_say->say_str));
	free(to_say->say_str);
	pthread_mutex_unlock(to_say->say_mutex);
	pthread_detach(to_say->say_thread_id);
	return (0);
}

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
	t_to_say				*to_say;

	if (!*self->simulation && what != SAY_DEAD)
		return ;
	to_say = (t_to_say*)malloc(sizeof(t_to_say));
	// check malloc error
	to_say->say_str_len = 35 + ft_ilen(self->num);
	to_say->say_mutex = self->say_mutex;
	to_say->what = what;
	to_say->simulation = self->simulation;
	to_say->say_str = (char*)malloc(sizeof(char) * to_say->say_str_len);
	// check malloc error
	memset(to_say->say_str, '\0', to_say->say_str_len);
	form_say_string(to_say->say_str, ts / 1000, self->num, g_phrases[what]);
	pthread_create(&to_say->say_thread_id, NULL, say_thread, to_say);
	// check on pthread errors;
}

void	phil_take_fork(t_philosopher *self, enum e_forks frk)
{
	if (!*self->simulation)
		return ;
	if (frk == FORK_LEFT)
	{
		pthread_mutex_lock(self->l_fork);
		if (!*self->simulation)
			pthread_mutex_unlock(self->l_fork);
	}
	else if (frk == FORK_RIGHT)
	{
		pthread_mutex_lock(self->r_fork);
		if (!*self->simulation)
			pthread_mutex_unlock(self->r_fork);
	}
}

void	phil_drop_forks(t_philosopher *self)
{
	pthread_mutex_unlock(self->l_fork);
	pthread_mutex_unlock(self->r_fork);
}