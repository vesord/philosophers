/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:46:40 by matrus            #+#    #+#             */
/*   Updated: 2020/10/09 11:44:43 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static const char	*g_phrases[] =
{
	"has taken a fork",
	"is eating",
	"is sleeping",
	"is thinking",
	"died"
};

void	phil_eat(t_philosopher *self)
{
	static int finished_eat;

	if (!*self->simulation)
		return ;
	sem_wait(self->eatdeath_sem);
	self->last_eat_time = get_timestamp();
	sem_post(self->eatdeath_sem);
	if (self->need_to_eat_times >= 0 &&
		self->count_eat >= self->need_to_eat_times &&
		!finished_eat)
	{
		sem_post(self->finished_eat);
		finished_eat = !finished_eat;
	}
	ft_usleep(self->time_eat);
	self->count_eat++;
}

void	phil_sleep(t_philosopher *self)
{
	if (!*self->simulation)
		return ;
	ft_usleep(self->time_sleep);
}

void	phil_take_fork(t_philosopher *self)
{
	if (!*self->simulation)
		return ;
	sem_wait(self->forks_sem);
	if (!*self->simulation)
		sem_post(self->forks_sem);
}

void	phil_drop_forks(t_philosopher *self)
{
	sem_post(self->forks_sem);
	usleep(5);
	sem_post(self->forks_sem);
	usleep(5);
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
	sem_wait(self->say_sem);
	if (!*self->simulation && is_last_msg)
	{
		free(say_str);
		return ;
	}
	form_say_string(say_str, get_timestamp() / 1000, self->num,
					g_phrases[what]);
	if (what == SAY_DEAD)
		is_last_msg = !is_last_msg;
	write(1, say_str, ft_strlen(say_str));
	if (what != SAY_DEAD)
		sem_post(self->say_sem);
	free(say_str);
	usleep(5);
}
