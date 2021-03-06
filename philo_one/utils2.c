/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:21:02 by matrus            #+#    #+#             */
/*   Updated: 2020/10/06 13:21:23 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_usleep(time_t mcs)
{
	time_t		cur_time;

	cur_time = get_timestamp();
	mcs -= 50;
	while (get_timestamp() - cur_time < mcs)
		usleep(10);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n < -9)
			ft_putnbr_fd(n / 10 * -1, fd);
		ft_putchar_fd(n % 10 * -1 + '0', fd);
		return ;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}
