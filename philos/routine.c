/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:00:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/22 22:33:23 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	securing_forks(t_ph *ph)
{
	pthread_mutex_lock(&(ph->mutex[ph->pos]));
	ft_printf("has taken a fork", ph);
	if (ph->pos)
	{
		pthread_mutex_lock(&(ph->mutex[ph->pos - 1]));
		ft_printf("has taken a fork", ph);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&(ph->mutex[ph->nb - 1]));
		ft_printf("has taken a fork", ph);
		return (0);
	}
}

void	ft_eat(t_ph *ph)
{
	int	mode;

	mode = securing_forks(ph);
	gettimeofday(&(ph->vl), 0);
	ft_printf("is eating", ph);
	my_usleep(ph->time_to_eat);
	pthread_mutex_unlock(&(ph->mutex[ph->pos]));
	if (!mode)
		pthread_mutex_unlock(&(ph->mutex[ph->nb - 1]));
	else
		pthread_mutex_unlock(&(ph->mutex[ph->pos - 1]));
}

void	*ft_sleep(t_ph *ph)
{
	ft_printf("is sleeping", ph);
	my_usleep(ph->time_to_sleep);
	return (0);
}

int	died(t_ph *ph)
{
	pthread_mutex_lock(ph->death);
	if (!(*ph->died))
		return (1);
	pthread_mutex_unlock(ph->death);
	return (0);
}

void	*ft_routine(void *tmp)
{
	t_ph			*ph;
	int				i;
	int				nb = 0;

	ph = (t_ph *)tmp;
	if (ph->pos % 2)
		usleep(1000);
	i = 0;
	gettimeofday(&(ph->vl), 0);
	while (1)
	{
		if (died(ph))
			return (0);
		ft_eat(ph);
		nb++;
		if (ph->nb_to_eat > -1 && nb >= ph->nb_to_eat)
		{
			pthread_mutex_lock(ph->eat);
			(*(ph->check))--;
			pthread_mutex_unlock(ph->eat);
		}
		if (died(ph))
			return (0);
		ft_sleep(ph);
		if (died(ph))
			return (0);
		ft_printf("is thinking", ph);
	}
	return (0);
}
