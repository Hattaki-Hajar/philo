/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:00:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/17 22:56:54 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	securing_forks(t_ph *ph)
{
	struct timeval	vl;

	pthread_mutex_lock(&(ph->mutex[ph->pos]));
	gettimeofday(&vl, 0);
	printf("%ld: %d has taken a fork\n", convert_time(&vl) - convert_time(ph->init), ph->pos + 1);
	if (ph->pos)
	{
		pthread_mutex_lock(&(ph->mutex[ph->pos - 1]));
		return (1);
	}
	else
	{
		pthread_mutex_lock(&(ph->mutex[ph->nb - 1]));
		return (0);
	}
}

void	ft_eat(t_ph *ph)
{
	int	mode;

	mode = securing_forks(ph);
	gettimeofday(&(ph->vl), 0);
	printf("%ld: %d is eating\n", convert_time(&(ph->vl)) - convert_time(ph->init), ph->pos + 1);
	my_usleep(ph->time_to_eat * 1000);
	pthread_mutex_unlock(&(ph->mutex[ph->pos]));
	if (!mode)
		pthread_mutex_unlock(&(ph->mutex[ph->nb - 1]));
	else
		pthread_mutex_unlock(&(ph->mutex[ph->pos - 1]));
}

void	*ft_sleep(t_ph *ph)
{
	struct timeval	vl;

	gettimeofday(&vl, 0);
	printf("%ld: %d is sleeping\n", convert_time(&vl) - convert_time(ph->init), ph->pos + 1);
	my_usleep(ph->time_to_sleep * 1000);
	return (0);
}

void	*ft_routine(void *tmp)
{
	struct timeval	vl;
	t_ph			*ph;
	int				i;

	ph = (t_ph *)tmp;
	if (ph->pos % 2)
		usleep(1000);
	i = 0;
	while (1)
	{
		ft_eat(ph);
		ft_sleep(ph);
		gettimeofday(&vl, 0);
		printf("%ld: %d is thinking\n", convert_time(&vl) - convert_time(ph->init), ph->pos + 1);
	}
	return (0);
}
