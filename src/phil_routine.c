/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:16:17 by bclaeys           #+#    #+#             */
/*   Updated: 2024/09/26 16:31:40 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>

int	ft_lock_and_print(t_philosopher *philosopher, char *string)
{
	usleep(10);
	if (!(ft_death_check(philosopher)))
	{
		pthread_mutex_lock(&philosopher->general_data->printf_mutex);
		ft_printf(string, ft_gettime(philosopher), philosopher->phil_id);
		pthread_mutex_unlock(&philosopher->general_data->printf_mutex);
	}
	else
		return (1);
	return (0);
}

int	ft_eat(t_philosopher *philosopher)
{
	int	death_check;

	death_check = 0;
	if (ft_lock_forks(philosopher) == 1)
		return (1);
	philosopher->time_last_eaten = ft_gettime(philosopher);
	death_check = ft_eat_and_drop_forks(philosopher);
	pthread_mutex_lock(&philosopher->general_data->forkcheck_mutex);
	if (philosopher->general_data->times_to_eat != -1)
		philosopher->times_eaten--;
	pthread_mutex_unlock(&philosopher->general_data->forkcheck_mutex);
	return (death_check);
}

int	ft_think(t_philosopher *philosopher)
{
	if (check_if_phil_died(philosopher))
		return (ft_die(philosopher), 0);
	if (ft_lock_and_print(philosopher, "%u %i is thinking\n"))
		return (1);
	if (check_if_phil_died(philosopher))
		return (ft_die(philosopher), 0);
	return (0);
}

int	ft_sleep(t_philosopher *philosopher)
{
	unsigned long	time;

	time = ft_gettime(philosopher);
	(philosopher)->time_last_slept = time;
	if (ft_lock_and_print(philosopher, "%u %i is sleeping\n"))
		return (1);
	while (ft_gettime(philosopher) <= (time
			+ philosopher->general_data->time_sleeping))
	{
		usleep(100);
		if (check_if_phil_died(philosopher))
			return (ft_die(philosopher));
	}
	return (0);
}

int	ft_die(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->general_data->death_mutex);
	pthread_mutex_lock(&philosopher->general_data->printf_mutex);
	if (philosopher->general_data->death_check == 0)
		ft_printf("%u %i died\n", philosopher->time_of_death,
			philosopher->phil_id);
	philosopher->general_data->death_check = 1;
	pthread_mutex_unlock(&philosopher->general_data->printf_mutex);
	pthread_mutex_unlock(&philosopher->general_data->death_mutex);
	return (1);
}
