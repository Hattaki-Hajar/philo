/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:56:22 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/20 19:01:54 by hhattaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define INIT 1
# define DESTROY 0

typedef struct s_ph
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*death;
	struct timeval	init;
	struct timeval	vl;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	int				nb_to_eat;
	int				pos;
	int				nb;
}	t_ph;

/*-------utils-------*/
long	convert_time(struct timeval *init);
void	ft_putendl_fd(char	*s);
int		ft_atoi(char *str);
void	my_usleep(int time);

/*------routine------*/
void	ft_eat(t_ph *ph);
void	*ft_sleep(t_ph *ph);
void	*ft_routine(void *tmp);

#endif