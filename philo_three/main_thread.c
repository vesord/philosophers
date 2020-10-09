/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:15:21 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 15:15:22 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	killing(t_philosopher **party, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		kill(party[i]->philo_pid, 9);
		i++;
	}
}

static void	clear_restaurant(t_philosopher **party, int count)
{
	int	i;

	sem_wait(party[0]->simulation_sem);
	killing(party, count);
	i = -1;
	while (++i < count)
		sem_close(party[i]->eatdeath_sem);
	sem_close(party[0]->say_sem);
	sem_close(party[0]->forks_sem);
	sem_close(party[0]->simulation_sem);
	i = -1;
	while (++i < count)
		free(party[i]);
	free(party);
}

static void	*control_simulation(void *arg)
{
	int				i;
	int				philo_count;
	t_philosopher	**party;

	party = (t_philosopher**)arg;
	philo_count = party[0]->philos;
	i = 0;
	while (i < philo_count)
	{
		sem_wait(party[i]->finished_eat);
		i++;
	}
	sem_wait(party[0]->say_sem);
	sem_post(party[0]->simulation_sem);
	return ((void*)0);
}

int			error_on_forking(t_philosopher **party, int i)
{
	while (i > 0)
	{
		kill(party[i - 1]->philo_pid, 9);
		i--;
	}
	return (1);
}

int			main_thread(t_args *arg)
{
	t_philosopher	**party;
	time_t			simulation;
	int				i;
	pthread_t		tid;

	party = NULL;
	if (!(party = initialization(arg, &simulation)))
		return (1);
	simulation = 0;
	if (arg->eat_count >= 0)
	{
		pthread_create(&tid, NULL, control_simulation, party);
		pthread_detach(tid);
	}
	i = -1;
	while (++i < arg->philos)
	{
		party[i]->philo_pid = fork();
		if (party[i]->philo_pid < 0)
			return (error_on_forking(party, i));
		else if (party[i]->philo_pid == 0)
			philo_process(party[i]);
	}
	clear_restaurant(party, arg->philos);
	return (0);
}
