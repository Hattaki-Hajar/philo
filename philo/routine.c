/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:00:20 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/13 19:34:09 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_ph ph)
{
	int	mode;

	mode = 1;
	pthread_mutex_lock(ph.mutex + ph.ph_pos);
	if (ph.ph_pos)
		pthread_mutex_lock(ph.mutex + (ph.ph_pos - 1));
	else
	{
		pthread_mutex_lock(ph.mutex + ph.ph_nb);
		mode = 0;
	}
	my_usleep(ph.time_to_eat);
	pthread_mutex_unlock(ph.mutex + ph.ph_pos);
	if (mode)
		pthread_mutex_unlock(ph.mutex + (ph.ph_pos - 1));
	else
		pthread_mutex_unlock(ph.mutex + ph.ph_nb);
}

void	*ft_sleep(void *meh)
{
	t_ph	*ph;

	ph = (t_ph *)meh;
	my_usleep(ph->time_to_sleep);
	printf("%d\n", ph->time_to_sleep);
	return (0);
}
