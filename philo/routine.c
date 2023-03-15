/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:00:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/15 00:56:08 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	securing_forks(t_ph *ph)
{
	struct timeval	vl;
	int				mode;

	mode = 1;
	pthread_mutex_lock(&(ph->mutex[ph->ph_pos]));
	gettimeofday(&vl, 0);
	if (((ph->vl->tv_sec * 1000) + ph->vl->tv_usec) - ((vl.tv_sec * 1000) + vl.tv_usec) >= ph->time_to_die)
			return (-1);
	printf("%ld %d has taken a fork\n", vl.tv_sec, ph->ph_pos + 1);
	if (ph->ph_pos)
	{
		pthread_mutex_lock(&(ph->mutex[ph->ph_pos - 1]));
		gettimeofday(&vl, 0);
		if (((ph->vl->tv_sec * 1000) + ph->vl->tv_usec) - ((vl.tv_sec * 1000) + vl.tv_usec) >= ph->time_to_die)
			return (-1);
	printf("%ld %d has taken a fork\n", vl.tv_sec, ph->ph_pos + 1);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&(ph->mutex[ph->ph_nb - 1]));
		gettimeofday(&vl, 0);
		if (((ph->vl->tv_sec * 1000) + ph->vl->tv_usec) - ((vl.tv_sec * 1000) + vl.tv_usec) >= ph->time_to_die)
			return (-1);
	printf("%ld %d has taken a fork\n", vl.tv_sec, ph->ph_pos + 1);
		return (0);
	}
}

int	ft_eat(t_ph *ph)
{
	struct timeval	vl;
	int				mode;

	mode = securing_forks(ph);
	gettimeofday(&vl, 0);
	if (mode == -1)
	{
		printf("%ld %d died\n", vl.tv_sec, ph->ph_pos + 1);
		return (0);
	}
	printf("%ld %d is eating\n", vl.tv_sec, ph->ph_pos + 1);
	my_usleep(ph->time_to_eat);
	pthread_mutex_unlock(&(ph->mutex[ph->ph_pos]));
	if (!mode)
		pthread_mutex_unlock(&(ph->mutex[ph->ph_pos - 1]));
	else
		pthread_mutex_unlock(&(ph->mutex[ph->ph_nb - 1]));
	return (1);
}

void	*ft_sleep(t_ph *ph)
{
	struct timeval	vl;

	gettimeofday(&vl, 0);
	printf("%ld %d is sleeping\n", vl.tv_sec, ph->ph_pos + 1);
	my_usleep(ph->time_to_sleep);
	return (0);
}

void	*ft_routine(void *tmp)
{
	t_ph			*ph;
	int				r;
	int				i;

	ph = (t_ph *)tmp;
	i = 0;
	while (1)
	{
		gettimeofday(ph->vl, 0);
		r = ft_eat(ph);
		if (!r)
		{
			ph->death = 0;	
			return (0);
		}
		ft_sleep(ph);
		printf("%d is thinking\n", ph->ph_pos + 1);
	}
	return (0);
}
