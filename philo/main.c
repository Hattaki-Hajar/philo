/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:31:42 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/13 21:44:54 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_ph *ph, int ac, char **av)
{
	ph->ph_nb = ft_atoi(av[1]);
	ph->time_to_die = ft_atoi(av[2]) * 1000;
	ph->time_to_eat = ft_atoi(av[3]) * 1000;
	ph->time_to_sleep = ft_atoi(av[4]) * 1000;
	ph->mutex = (pthread_mutex_t *)malloc(ph->ph_nb * sizeof(pthread_mutex_t));
	if (ac == 6)
		ph->nb_to_eat = ft_atoi(av[5]);
	else
		ph->nb_to_eat = -1;
	ph->death = 1;
}

void	create_and_wait_for_threads(pthread_t *id, int ac, char **av, t_ph *ph)
{
	int		i;
	int		ph_nb;

	i = 0;
	ph_nb = ft_atoi(av[1]);
	while (i < ph_nb)
	{
		init_struct(ph + i, ac, av);
		(ph + i)->ph_pos = i;
		pthread_create(id + i, NULL, ft_sleep, ph + i);
		i++;
	}
	i = 0;
	while (i < ph_nb)
	{
		pthread_join(id[i], NULL);
		i++;
	}
}

void	mutex_init_or_destroy(pthread_mutex_t *id, int fork_num, int mode)
{
	int	i;

	i = 0;
	// 1 to init 0 to destroy
	if (mode)
	{
		while (i < fork_num)
		{
			pthread_mutex_init(id + i, NULL);
			i++;
		}
	}
	else
	{
		while (i < fork_num)
		{
			pthread_mutex_destroy(id + i);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	pthread_t	*id;
	t_ph		*ph;
	int			ph_nb;

	(void)ac;
	if (ac > 6 || ac < 5)
		ft_putendl_fd("Error: wrong number of arguments");
	ph_nb = ft_atoi(av[1]);
	// init_struct(&ph, ac, av);
	id = (pthread_t *)malloc(ph_nb * sizeof(pthread_t));
	ph = (t_ph *)malloc(ph_nb * sizeof(t_ph));
	mutex_init_or_destroy(ph->mutex, ph_nb, INIT);
	create_and_wait_for_threads(id, ac, av, ph);
}
