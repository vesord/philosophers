/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:21:02 by matrus            #+#    #+#             */
/*   Updated: 2020/10/09 11:40:24 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

void	form_eatdeath_sem_name(char *dst, const char *common_part, int num)
{
	int i;
	int num_len;
	int tmp;

	i = -1;
	while (common_part[++i])
		dst[i] = common_part[i];
	num_len = ft_ilen(num);
	tmp = i;
	i--;
	while (++i < tmp + num_len)
		dst[i] = (num / ft_pow(10, tmp - 1 + num_len - i)) % 10 + '0';
	dst[i] = '\0';
}

int		philo_sem_open(sem_t **dst, const char *name, int value)
{
	sem_unlink(name);
	if ((*dst = sem_open(name, O_CREAT | O_EXCL, 0644, value)) == SEM_FAILED)
		return (1);
	return (0);
}
