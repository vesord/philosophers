/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:36:27 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 18:36:29 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

const char				*forks_sem_name = "philo_forks";
const char				*say_sem_name = "philo_say";
const char				*eatdeath_sem_name_common = "philo_eatdeath";
const char				*servant_sem_name = "philo_servant";

static t_philosopher	*philosopher_init(t_args *arg, int i,
															time_t *simulation)
{
	t_philosopher	*kant;
	char			*eatdeath_sem_name;

	if (!(eatdeath_sem_name = (char*)malloc(sizeof(char) *
		(ft_strlen(eatdeath_sem_name_common) + ft_ilen(i) + 1))))
		return (NULL);
	if (!(kant = (t_philosopher*)malloc(sizeof(t_philosopher))))
		return (NULL);
	kant->num = i + 1;
	kant->simulation = simulation;
	kant->last_eat_time = 0;
	kant->time_eat = arg->time_eat * 1000;
	kant->time_sleep = arg->time_sleep * 1000;
	kant->time_to_die = arg->time_die * 1000;
	kant->count_eat = 0;
	kant->eat = phil_eat;
	kant->sleep = phil_sleep;
	kant->say = phil_say; // TODO: init philo is ready
	kant->take_fork = phil_take_fork;
	kant->drop_forks = phil_drop_forks;
	form_eatdeath_sem_name(eatdeath_sem_name, eatdeath_sem_name_common, i);
	if (philo_sem_open(&kant->eatdeath_sem, eatdeath_sem_name, 0))
		return (NULL);
	free(eatdeath_sem_name);
	return (kant);
}

static int				party_init(t_philosopher **party, t_args *arg,
															time_t *simulation)
{
	sem_t			*forks_sem;
	sem_t			*say_sem;
	sem_t			*servant_sem;
	int				i;

	if (philo_sem_open(&say_sem, say_sem_name, 1))
		return (1);
	if (philo_sem_open(&forks_sem, forks_sem_name, arg->philos))
		return (1);
	if (philo_sem_open(&servant_sem, servant_sem_name, arg->philos / 2))
		return (1);
	i = -1;
	while (++i < arg->philos)
	{
		if (!(party[i] = philosopher_init(arg, i, simulation)))
			return (1);
		party[i]->forks_sem = forks_sem;
		party[i]->say_sem = say_sem;
		party[i]->servant_sem = servant_sem;
	}
	return (0);
}

t_philosopher			**initialization(t_args *arg, time_t *simulation)
{
	t_philosopher **party;

	if (!(party = (t_philosopher**)malloc(sizeof(t_philosopher*) *
																arg->philos)))
		return (NULL);
	if (party_init(party, arg, simulation))
		return (NULL);
	return (party);
}
