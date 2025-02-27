/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:38:40 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/26 18:38:09 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	_print(t_philo *philo, const char *msg)
{
	int	is_eating;

	is_eating = ft_strcmp(msg, EAT);
	sem_wait(philo->data->print);
	printf("%zu	%d	%s\n", ft_current_time(philo->data->time_start), philo->id, msg);
	if (!is_eating)
	{
		philo->last_meal_time = ft_current_time(philo->data->time_start);
		philo->meals_eaten++;
	}
	sem_post(philo->data->print);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	size_t	current_time;

	philo = (t_philo *)arg;
	while (1)
	{
		current_time = ft_current_time(philo->data->time_start);
		if (current_time - philo->last_meal_time > philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("%zu	%d	died\n", current_time, philo->id);
			sem_post(philo->data->died);
			return (NULL);
		}
	}
	return (NULL);
}

void	philos_routine(t_philo *philo)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, &monitor_routine, philo);
	pthread_detach(monitor_thread);
	while (1)
	{
		sem_wait(philo->data->port);
		sem_wait(philo->data->forks);
		_print(philo, FORK);
		sem_wait(philo->data->forks);
		_print(philo, FORK);
		_print(philo, EAT);
		_usleep(philo->data->time_to_eat);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		sem_post(philo->data->port);
		if (philo->data->eat_limit != -1 &&
			philo->meals_eaten >= philo->data->eat_limit)
		{
			sem_post(philo->data->eat);
			philo->data->eat_limit = -1;
		}
		_print(philo, SLP);
		_usleep(philo->data->time_to_sleep);
		_print(philo, THINK);
		usleep(100);
	}
}

void	single_philo_routine(t_philo *philo)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, &monitor_routine, philo);
	sem_wait(philo->data->forks);
	_print(philo, FORK);
	usleep(philo->data->time_to_die * 1000);
	_print(philo, "died");
	sem_post(philo->data->forks);
}

void	start_dining(t_data *data)
{
	t_philo	philo[999];

	init_sema(data);
	init_dining(data, philo);
	if (data->nbr_philo == 1)
		create_process(philo, &single_philo_routine, data->nbr_philo);
	else
		create_process(philo, &philos_routine, data->nbr_philo);
	monitor_philosophers(philo);
	cleanup_the_table(data);
}
