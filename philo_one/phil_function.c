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

static const char	*g_phrases[] =
{
	"has taken a fork",
	"is eating",
	"is sleeping",
	"is thinking",
	"died"
};

extern time_t		g_cur_time;

void	phil_eat(t_philosopher *self)
{
	if (!*self->simulation)
		return ;
	pthread_mutex_lock(self->eatdeath_mutex);
	self->last_eat_time = g_cur_time;
	self->count_eat++;
	pthread_mutex_unlock(self->eatdeath_mutex);
	ft_usleep(self->time_eat);
}

void	phil_sleep(t_philosopher *self)
{
	if (!*self->simulation)
		return ;
	ft_usleep(self->time_sleep);
}

void	phil_say(t_philosopher *self, enum e_phrases what)
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
	pthread_mutex_lock(self->say_mutex);
	if (!*self->simulation && is_last_msg)
	{
		free(say_str);
		return ;
	}
	form_say_string(say_str, g_cur_time, self->num,
															g_phrases[what]);
	if (what == SAY_DEAD)
		is_last_msg = !is_last_msg;
	write(1, say_str, ft_strlen(say_str));
	pthread_mutex_unlock(self->say_mutex);
	free(say_str);
//	usleep(100);
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
	else
	{
		pthread_mutex_lock(self->r_fork);
		if (!*self->simulation)
			pthread_mutex_unlock(self->r_fork);
	}
}

void	phil_drop_forks(t_philosopher *self, int order)
{
	if (order)
	{
		pthread_mutex_unlock(self->r_fork);
		pthread_mutex_unlock(self->l_fork);
	}
	else
	{
		pthread_mutex_unlock(self->l_fork);
		pthread_mutex_unlock(self->r_fork);
	}
}
