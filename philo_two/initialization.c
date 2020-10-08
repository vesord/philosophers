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
	kant->say = phil_say;
	kant->take_fork = phil_take_fork;
	kant->drop_forks = phil_drop_forks;
	form_eatdeath_sem_name(eatdeath_sem_name, eatdeath_sem_name_common, i); // TODO:debug check
	if ((kant->eatdeath_sem = sem_open(eatdeath_sem_name, O_CREAT, 0644,
															0)) == SEM_FAILED)
		return (NULL);
	free(eatdeath_sem_name);
	return (kant);
}

static int				party_init(t_philosopher **party, t_args *arg,
															time_t *simulation)
{
	sem_t			*forks_sem;
	sem_t			*say_sem;
	int				i;

	if ((forks_sem = sem_open(forks_sem_name, O_CREAT, 0644,
													arg->philos)) == SEM_FAILED)
		return (1);
	if ((say_sem = sem_open(say_sem_name, O_CREAT, 0644, 1)) == SEM_FAILED)
		return (1);
	i = -1;
	while (++i < arg->philos)
	{
		if (!(party[i] = philosopher_init(arg, i, simulation)))
			return (1);
		party[i]->forks_sem = forks_sem;
		party[i]->say_sem = say_sem;
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
