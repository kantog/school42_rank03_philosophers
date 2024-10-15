/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_free_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:55:22 by bclaeys           #+#    #+#             */
/*   Updated: 2024/09/26 16:36:59 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int	ft_lock_forks(t_philosopher *philosopher)
{
	if (philosopher->phil_id % 2 == 1)
	{
		pthread_mutex_lock(&philosopher->neighbour->fork);
		if (check_if_phil_died(philosopher))
		{
			philosopher->time_of_death = philosopher->time_last_eaten
				+ philosopher->general_data->time_till_death;
			pthread_mutex_unlock(&philosopher->neighbour->fork);
			return (ft_die(philosopher));
		}
		pthread_mutex_lock(&philosopher->fork);
	}
	else
	{
		pthread_mutex_lock(&philosopher->fork);
		if (check_if_phil_died(philosopher))
		{
			philosopher->time_of_death = philosopher->time_last_eaten
				+ philosopher->general_data->time_till_death;
			pthread_mutex_unlock(&philosopher->fork);
			return (ft_die(philosopher));
		}
		pthread_mutex_lock(&philosopher->neighbour->fork);
	}
	return (0);
}

int	check_if_phil_died(t_philosopher *philosopher)
{
	if (ft_gettime(philosopher) >= philosopher->general_data->time_till_death
		+ philosopher->time_last_eaten)
	{
		philosopher->time_of_death = ft_gettime(philosopher);
		return (1);
	}
	return (0);
}

int	ft_unlock_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->neighbour->fork);
	pthread_mutex_unlock(&philosopher->fork);
	return (0);
}

int	join_phils(t_philosopher *philosopher, char **av)
{
	int				i;
	t_philosopher	*current_phil;

	i = 1;
	current_phil = philosopher;
	while (i <= ft_atoi(av[1]))
	{
		if ((pthread_join(current_phil->thread_id, NULL)))
		{
			write(2, "something went wrong while joining the threads", 29);
			return (1);
		}
		usleep(300);
		current_phil = current_phil->neighbour;
		i++;
	}
	return (0);
}
