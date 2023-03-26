/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:21:21 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/26 03:51:38 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_ph(char **av, t_ph_b *ph, pid_t *id, int *ph_nb)
{
	int	i;
	int	args[3];

	args[0] = ft_atoi(av[2]);
	args[1] = ft_atoi(av[3]);
	args[2] = ft_atoi(av[4]);
	if (args[0] <= 0 || args[1] <= 0 || args[2] <= 0)
	{
		ft_putendl_fd("Error: Inavlid argument");
		exit (-1);	
	}
	i = 0;
	while (i < *ph_nb)
	{
		(ph + i)->ph_nb = ph_nb;
		(ph + i)->t_die = args[0];
		(ph + i)->t_eat = args[1];
		(ph + i)->t_sleep = args[2];
		(ph + i)->id = id + i;
		i++;
	}
}

void	ft_init(int ac, char **av, t_ph_b *ph, sem_t *forks)
{
	struct timeval	init;
	int				nb_eat;
	int				nb;
	int				i;
	
	i = 0;
	nb = ft_atoi(av[1]);
	nb_eat = -1;
	if (ac == 6)
	{
		nb_eat = ft_atoi(av[5]);
		if (nb_eat <= 0)
			exit (ft_putendl_fd("Error: Invalid argument"));
	}
	gettimeofday(&init, 0);
	while (i < nb)
	{
		(ph + i)->forks = forks;
		(ph + i)->nb_eat = nb_eat;
		(ph + i)->pos = i;
		(ph + i)->init = &init;
		i++;
	}
}

void	check_ph(t_ph_b *ph)
{
	struct timeval	vl;

	while (1)
	{
		gettimeofday(&vl, 0);
		if (convert_time(&vl) - convert_time(&(ph->vl)) >= ph->t_die)
		{
			printf("here\n");
			exit (ph->pos);
		}
	}
}

void	create_process(t_ph_b *ph, pid_t *id)
{
	pthread_t	*thread;
	struct timeval	vl;
	int			i;
	int			status;
	int			nb;

	i = 0;
	nb = *(ph->ph_nb);
	thread = malloc(nb * sizeof(pthread_t));
	while (i < nb)
	{
		if (ph->pos % 2)
			my_usleep(1000);
		id[i] = fork();
		if (id[i])
		{
			(ph + i)->id = id;
			pthread_create(thread + i, 0, routine_b, ph + i);
			pthread_detach(thread[i]);
			exit(0);
		}
		i++;
	}
	free(thread);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		gettimeofday(&vl, 0);
		printf("%ld: %d died\n", (convert_time(&vl) - convert_time(ph->init)), status + 1);
	}
	i = 0;
	while (i < nb)
	{
		if ((ph + i)->pos != status)
			kill(*((ph + i)->id), SIGKILL);
		i++;
	}
	
}

int main(int ac, char **av)
{
	pid_t	*id;
	t_ph_b	*ph;
	int		*ph_nb;
	sem_t	*forks;

	if (ac < 5 || ac > 6)
		return (ft_putendl_fd("Error: Wrong number of arguments"));
	ph_nb = malloc(sizeof(int));
	*ph_nb = ft_atoi(av[1]);
	if (*ph_nb <= 0)
		return (ft_putendl_fd("Error: Invalid argument"));
	id = (pid_t *)malloc(*ph_nb * sizeof(pid_t));
	ph = (t_ph_b *)malloc(*ph_nb * sizeof(t_ph_b));
	init_ph(av, ph, id, ph_nb);
	forks = sem_open("forks", O_CREAT, O_RDWR, *ph_nb);
	ft_init(ac, av, ph, forks);
	int i = 0;
	while (i < *ph_nb)
	{
		printf("%p\n", (ph + i)->init);
		i++;
	}
	// create_process(ph, id);
	sem_close(forks);
	sem_unlink("forks");
}