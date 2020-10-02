/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 17:03:16 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 17:03:18 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <sys/time.h>
#include <pthread.h>

typedef struct	s_philosopher
{
	pthread_t		thread_id;
	int				num;
	int				time_eat;
	int				time_sleep;

	suseconds_t		*simulation;
	int				last_eat_time;
	int				is_dead;
	int				count_eat;
	void			(*eat)(struct s_philosopher *self);
	void			(*sleep)(struct  s_philosopher *self);
	void			(*say)(struct s_philosopher *self, char *phrase,
		suseconds_t ts);
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}				t_philosopher;

#endif
