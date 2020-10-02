/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:31:29 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 14:31:33 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include "philosopher.h"

typedef struct	s_args
{
	int		philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		eat_count;
}				t_args;

void	print_help();
int		set_arg(t_args *arg, int argc, char **argv);
int		main_thread(t_args *arg);

int		initialization(t_philosopher **party, t_args *arg,
					suseconds_t *simulation);


void	phil_say(t_philosopher *self, char *phrase, suseconds_t ts);
void	phil_sleep(t_philosopher *self);
void	phil_eat(t_philosopher *self);

#endif
