/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:38:40 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/19 09:01:07 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	_print(t_philo *philo, const char *msg)
{
	int	over;
	int	is_eating;

	pthread_mutex_lock(&philo->data->check_finish);
	over = philo->data->dining_over;
	pthread_mutex_unlock(&philo->data->check_finish);
	if (over)
		return (1);
	is_eating = ft_strcmp(msg, EAT);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%zu	%d	%s\n",
		ft_current_time(philo->data->time_start), philo->id, msg);
	if (is_eating == 0)
	{
		philo->last_meal_time = ft_current_time(philo->data->time_start);
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}

void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo->right_fork);
		_print(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		_print(philo, FORK);
		if (_print(philo, EAT))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (_print(philo, SLP))
			break;
		usleep(philo->data->time_to_sleep * 1000);
		if (_print(philo, THINK))
			break ;
	}
	return (NULL);
}

void	*single_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	_print(philo, FORK);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	start_dining(t_data *data)
{
	t_philo			*philo;
	t_mutex			*forks;

	if (allocation(data->nbr_philo, &philo, &forks))
		return ;
	init_dining(data, philo, forks);
	if (data->nbr_philo == 1)
		manage_threads(philo, &single_philo_routine, data->nbr_philo, 1);
	else
		manage_threads(philo, &philos_routine, data->nbr_philo, 1);
	monitor_philosophers(philo);
	manage_threads(philo, NULL, data->nbr_philo, 0);
	cleanup_the_table(data, philo, forks);
}
