/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:37:34 by bclaeys           #+#    #+#             */
/*   Updated: 2024/09/26 15:31:12 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "philo.h"
#include <sys/time.h>

int	ft_eat_and_drop_forks(t_philosopher *philosopher)
{
	unsigned long	time;
	int				death;

	time = ft_gettime(philosopher);
	(philosopher)->time_last_slept = time;
	death = ft_lock_and_print(philosopher, "%u %i has taken a fork\n");
	if (!(ft_death_check(philosopher)))
	{
		pthread_mutex_lock(&philosopher->general_data->printf_mutex);
		ft_printf("%u %i is eating\n", philosopher->time_last_eaten,
			philosopher->phil_id);
		pthread_mutex_unlock(&philosopher->general_data->printf_mutex);
	}
	while (ft_gettime(philosopher) < (time
			+ philosopher->general_data->time_eating))
	{
		usleep(100);
		if (check_if_phil_died(philosopher))
			return (ft_unlock_forks(philosopher) + ft_die(philosopher));
	}
	ft_unlock_forks(philosopher);
	return (death);
}

int	ft_death_check(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->general_data->death_mutex);
	if (philosopher->general_data->death_check == 1)
	{
		pthread_mutex_unlock(&philosopher->general_data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->general_data->death_mutex);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	temp_value;

	i = 0;
	temp_value = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		temp_value = temp_value * 10 + (str[i] - 48);
		if (temp_value > LONG_MAX)
			return (0);
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return ((int)(temp_value));
}

unsigned long	ft_gettime(t_philosopher *philosopher)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000)
		- philosopher->general_data->starting_time);
}
