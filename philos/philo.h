/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhattaki <hhattaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:56:22 by hhattaki          #+#    #+#             */
/*   Updated: 2023/03/23 21:21:06 by hhattaki         ###   ########.fr       */
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
	pthread_mutex_t	*eat;
	struct timeval	*init;
	struct timeval	vl;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	int				nb_to_eat;
	int				*died;
	int				pos;
	int				nb;
	int				*check;
}	t_ph;

/*-------utils-------*/
int		init_struct(t_ph *ph, int ac, char **av, struct timeval *vl_init);
long	convert_time(struct timeval *init);
void	ft_printf(char *str, t_ph *ph);
void	ft_putendl_fd(char	*s);
void	my_usleep(int time);
int		ft_atoi(char *str);

/*------routine------*/
void	ft_eat(t_ph *ph);
void	*ft_sleep(t_ph *ph);
void	*ft_routine(void *tmp);

#endif