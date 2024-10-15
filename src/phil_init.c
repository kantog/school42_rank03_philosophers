/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:46:38 by bclaeys           #+#    #+#             */
/*   Updated: 2024/09/26 15:55:31 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static void	mutex_init(t_general_data *general_data)
{
	pthread_mutex_init(&general_data->printf_mutex, NULL);
	pthread_mutex_init(&general_data->death_mutex, NULL);
	pthread_mutex_init(&general_data->forkcheck_mutex, NULL);
}

int	ft_init_current(t_philosopher *current_phil)
{
	pthread_mutex_init(&current_phil->fork, NULL);
	if (pthread_create(&current_phil->thread_id, NULL, &philosopher_routine,
			(void *)(current_phil)))
		return (-1);
	return (0);
}

static int	threads_init(t_philosopher *philosopher, int number_phils)
{
	int				i;
	t_philosopher	*current_phil;

	i = 1;
	current_phil = philosopher;
	while (1)
	{
		if (ft_init_current(current_phil) == -1)
			return (-1);
		i++;
		if (i > number_phils)
			break ;
		current_phil++;
	}
	return (0);
}

void	ft_init_data(char **av, int ac, t_general_data *general_data)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	general_data->time_till_death = ft_atoi(av[2]);
	general_data->time_eating = ft_atoi(av[3]);
	general_data->time_sleeping = ft_atoi(av[4]);
	if (ac == 6)
		general_data->times_to_eat = ft_atoi(av[5]);
	else
		general_data->times_to_eat = -1;
	general_data->death_check = 0;
	general_data->start_check = 0;
	general_data->starting_time = (time.tv_sec * 1000 + time.tv_usec / 1000)
		+ 10;
}

int	ft_init_philosophers(t_philosopher *philosopher,
		t_general_data *general_data, int number_phils)
{
	int				i;
	t_philosopher	*current_phil;
	t_philosopher	*temp_phil;

	i = 1;
	current_phil = philosopher;
	mutex_init(general_data);
	while (1)
	{
		temp_phil = current_phil;
		current_phil->phil_id = i;
		current_phil->times_eaten = general_data->times_to_eat;
		current_phil->time_last_eaten = 0;
		current_phil->time_of_death = 0;
		current_phil->general_data = general_data;
		i++;
		if (i > number_phils)
			break ;
		current_phil++;
		temp_phil->neighbour = current_phil;
	}
	current_phil->neighbour = philosopher;
	if (threads_init(philosopher, number_phils) == -1)
		return (-1);
	return (0);
}
