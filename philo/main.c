/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:31:42 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/20 19:08:10 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_ph *ph, int ac, char **av)
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
}

void	create_and_wait_for_threads(pthread_t *id, int ac, char **av, t_ph *ph)
{
	struct timeval	vl;
	int				i;
	int				ph_nb;

	i = 0;
	ph_nb = ft_atoi(av[1]);
	gettimeofday(&(ph->init), 0);
	while (i < ph_nb)
	{
		(ph + i)->nb = ph_nb;
		(ph + i)->pos = i;
		init_struct(ph + i, ac, av);
		pthread_create(id + i, NULL, ft_routine, ph + i);
		i++;
	}
	usleep(200);
	while (1)
	{
		i = 0;
		while (i < ph_nb)
		{
			gettimeofday(&vl, 0);
			// printf("%ld %ld\n", convert_time(&(vl)) - convert_time(&(ph->vl)), ph->time_to_die);
			if (convert_time(&(vl)) - convert_time(&(ph->vl)) >= ph->time_to_die)
			{
				printf("%ld: %d died\n", convert_time(&vl) - convert_time(&(ph->init)), ph->pos + 1);
				// pthread_mutex_lock(ph->death);
				// ph->death = 0;
				// pthread_mutex_unlock(ph->death);
				return ;
			}
			// printf ("-->%ld\n", convert_time(&(vl)) - convert_time(&(ph->vl)));
			i++;
		}
	}
	i = 0;
	while (i < ph_nb)
	{
		pthread_detach(id[i]);
		i++;
	}
}

void	mutex_init_or_destroy(pthread_mutex_t *id, int num, int mode)
{
	// pthread_mutex_t	*death;
	int				i;

	i = 0;
	if (mode == INIT)
	{
		while (i < num)
		{
			pthread_mutex_init(id + i, NULL);
			i++;
		}
	}
	else if (mode == DESTROY)
	{
		while (i < num)
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
	pthread_mutex_t	*death;
	pthread_mutex_t	*mutex;
	int				ph_nb;
	int				i;

	(void)ac;
	if (ac > 6 || ac < 5)
		ft_putendl_fd("Error: wrong number of arguments");
	ph_nb = ft_atoi(av[1]);
	if (ft_atoi(av[1]) <= 0)
		ft_putendl_fd("Error: Invalid argument");
	id = (pthread_t *)malloc(ph_nb * sizeof(pthread_t));
	ph = (t_ph *)malloc(ph_nb * sizeof(t_ph));
	mutex = (pthread_mutex_t *)malloc(ph_nb * sizeof(pthread_mutex_t));
	death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// death = mutex_init_or_destroy(mutex, ph_nb, INIT);
	pthread_mutex_init(death, 0);
	i = 0;
	while (i < ph_nb)
	{
		(ph + i)->mutex = mutex;
		(ph + i++)->death = death;
	}
	create_and_wait_for_threads(id, ac, av, ph);
	mutex_init_or_destroy(mutex, ph_nb, DESTROY);
	// pthread_mutex_destroy(death);
	// system("leaks philo");
}
