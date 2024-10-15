/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:14:20 by bclaeys           #+#    #+#             */
/*   Updated: 2024/09/26 16:46:29 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	usleep(10000);
	while (1)
	{
		if (ft_eat(philosopher) == 1)
			return (NULL);
		if (philosopher->times_eaten == 0)
			return (NULL);
		if (ft_sleep(philosopher) == 1)
			return (NULL);
		if (ft_think(philosopher) == 1)
			return (NULL);
		if (check_if_phil_died(philosopher) == 1)
			return (NULL);
		if (ft_death_check(philosopher) == 1)
			return (NULL);
	}
	return (NULL);
}

static int	destroy_mutex(t_philosopher **philosopher, char **av)
{
	t_philosopher	*current_phil;
	int				i;
	int				phil_amount;

	i = 1;
	phil_amount = ft_atoi(av[1]);
	current_phil = *philosopher;
	while (i <= phil_amount)
	{
		pthread_mutex_destroy(&current_phil->fork);
		current_phil = current_phil->neighbour;
		i++;
	}
	pthread_mutex_destroy(&(*philosopher)->general_data->printf_mutex);
	pthread_mutex_destroy(&(*philosopher)->general_data->death_mutex);
	pthread_mutex_destroy(&(*philosopher)->general_data->forkcheck_mutex);
	return (0);
}

int	main(int ac, char **av)
{
	t_philosopher	*philosophers;
	t_general_data	*general_data;

	general_data = malloc(sizeof(t_general_data));
	if (!general_data)
		return (write(2, "malloc failed\n", 14) - 15);
	if (ac != 5 && ac != 6)
		return (printf("Error: wrong number of args\n"));
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1
		|| ft_atoi(av[4]) < 1 || (ac == 6 && ft_atoi(av[5]) < 1))
		return (printf("Error: invalid arg\n"));
	ft_init_data(av, ac, general_data);
	if (ft_atoi(av[1]) == 1)
		return (ft_printf("%u 1 died\n", general_data->time_till_death), 0);
	philosophers = malloc(sizeof(t_philosopher) * ft_atoi(av[1]));
	if (!philosophers)
		return (write(2, "malloc failed\n", 14) - 15);
	if (ft_init_philosophers(philosophers, general_data, ft_atoi(av[1])))
		return (write(2, "init failed\n", 12) - 13);
	join_phils(philosophers, av);
	destroy_mutex(&philosophers, av);
	free(philosophers);
	free(general_data);
}
