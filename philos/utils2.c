/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:23:29 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/21 23:07:23 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	convert_time(struct timeval *init)
{
	long	res;

	res = (init->tv_sec * 1000) + (init->tv_usec / 1000);
	return (res);
}

void	init_struct(t_ph *ph, int ac, char **av, struct timeval *vl_init)
{
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		ft_putendl_fd("Error: Invalid argument");
	ph->time_to_die = ft_atoi(av[2]);
	ph->time_to_eat = ft_atoi(av[3]);
	ph->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		ph->nb_to_eat = ft_atoi(av[5]);
	else
		ph->nb_to_eat = -1;
	ph->init = vl_init;
}
