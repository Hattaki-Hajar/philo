/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:31:42 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/16 01:42:42 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_ph *ph, int ac, char **av, struct timeval *vl_init)
{
	ph->time_to_die = ft_atoi(av[2]) * 1000;
	ph->time_to_eat = ft_atoi(av[3]) * 1000;
	ph->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		ph->nb_to_eat = ft_atoi(av[5]);
	else
		ph->nb_to_eat = -1;
	ph->death = 1;
	gettimeofday(&(ph->vl), 0);
	ph->init = vl_init;
}

void	create_and_wait_for_threads(pthread_t *id, int ac, char **av, t_ph *ph)
{
	struct timeval	init;
	int				i;
	int				ph_nb;

	i = 0;
	ph_nb = ft_atoi(av[1]);
	gettimeofday(&init, 0);
	while (i < ph_nb)
	{
		(ph + i)->ph_nb = ph_nb;
		(ph + i)->ph_pos = i;
		init_struct(ph + i, ac, av, &init);
		if (i % 2)
			usleep(10);
		pthread_create(id + i, NULL, ft_routine, ph + i);
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < ph_nb)
		{
			if (!((ph + i)->death))
			{
				printf("%d died\n", ph->ph_pos + 1);
				return ;
			}
			i++;
		}
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
	pthread_t		*id;
	t_ph			*ph;
	pthread_mutex_t	*mutex;
	int				ph_nb;
	int				i;

	(void)ac;
	if (ac > 6 || ac < 5)
		ft_putendl_fd("Error: wrong number of arguments");
	ph_nb = ft_atoi(av[1]);
	id = (pthread_t *)malloc(ph_nb * sizeof(pthread_t));
	ph = (t_ph *)malloc(ph_nb * sizeof(t_ph));
	mutex = (pthread_mutex_t *)malloc(ph_nb * sizeof(pthread_mutex_t));
	mutex_init_or_destroy(mutex, ph_nb, INIT);
	i = 0;
	while (i < ph_nb)
		(ph + i++)->mutex = mutex;
	create_and_wait_for_threads(id, ac, av, ph);
	// mutex_init_or_destroy(mutex, ph_nb, DESTROY);
}
