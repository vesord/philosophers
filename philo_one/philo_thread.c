/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 17:25:48 by matrus            #+#    #+#             */
/*   Updated: 2020/10/03 17:48:21 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include "philosopher.h"

void	*philo_thread(void *arg)
{
	t_philosopher *dekart;

	dekart = (t_philosopher*)arg;
	while (!dekart->simulation)
		;
	// Here we should start life thread
	while (dekart->simulation)
	{
		dekart->take_fork(dekart, "left");
		dekart->say(dekart, "took fork!", get_timestamp());
		dekart->take_fork(dekart, "right");
		dekart->say(dekart, "took fork!", get_timestamp());
		dekart->say(dekart, "eating", get_timestamp());
		dekart->eat(dekart);
		dekart->say(dekart, "sleeping", get_timestamp());
		dekart->sleep(dekart);
		dekart->say(dekart, "thinking", get_timestamp());
	}
}
