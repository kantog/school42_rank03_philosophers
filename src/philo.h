/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:03:53 by bclaeys           #+#    #+#             */
/*   Updated: 2024/09/26 16:04:20 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <pthread.h>

typedef struct timeval	t_timeval;

typedef struct s_general_data
{
	pthread_mutex_t			printf_mutex;
	pthread_mutex_t			death_mutex;
	pthread_mutex_t			forkcheck_mutex;
	pthread_t				monitor_thread_id;
	int						death_check;
	int						start_check;
	int						times_to_eat;
	unsigned long			time_till_death;
	unsigned long			time_eating;
	unsigned long			time_sleeping;
	unsigned long			starting_time;
}	t_general_data;

typedef struct philosopher_s
{
	int						phil_id;
	unsigned long			time_last_eaten;
	unsigned long			time_last_slept;
	unsigned long			time_of_death;
	pthread_t				thread_id;
	pthread_mutex_t			fork;
	int						times_eaten;
	struct philosopher_s	*neighbour;
	t_general_data			*general_data;
}	t_philosopher;

int				ft_atoi(const char *str);
int				ft_init_philosophers(t_philosopher *philosopher,
					t_general_data *general_data, int number_phils);
void			*philosopher_routine(void *arg);
int				ft_eat(t_philosopher *philosopher);
int				ft_think(t_philosopher *philosopher);
int				ft_sleep(t_philosopher *philosopher);
int				ft_die(t_philosopher *philosopher);
unsigned long	ft_gettime(t_philosopher *philosopher);
int				join_phils(t_philosopher *philosopher, char **av);
int				ft_lock_and_print(t_philosopher *philosopher, char *string);
int				ft_death_check(t_philosopher *philosopher);
void			ft_init_data(char **av, int ac, t_general_data *general_data);
int				ft_eat_and_drop_forks(t_philosopher *philosopher);
int				check_if_phil_died(t_philosopher *philosopher);
int				ft_unlock_forks(t_philosopher *philosopher);
int				ft_lock_forks(t_philosopher *philosopher);

/* FT_PRINTF */

void			ft_format_and_count(char s, va_list ap, size_t *count);
size_t			ftpr_putchar(char c);
size_t			ftpr_puthex(size_t h, char c);
size_t			ftpr_putint(int n);
size_t			ftpr_putstr(char *s);
size_t			ftpr_putptr(size_t p);
size_t			ftpr_putunsdec(unsigned int d);
int				ft_printf(const char *s, ...);

#endif
