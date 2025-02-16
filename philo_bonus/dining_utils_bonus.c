/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:41:13 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/16 14:38:39 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sema(t_data *data)
{
	sem_unlink(FORK_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(DIE_SEM);
	sem_unlink(EAT_SEM);
	data->forks = sem_open(FORK_SEM, O_CREAT, 0644, data->nbr_philo);
	data->print = sem_open(PRINT_SEM, O_CREAT, 0644, 1);
	data->died = sem_open(DIE_SEM, O_CREAT, 0644, 0);
	data->eat = sem_open(EAT_SEM, O_CREAT, 0644, 0);
}

void	init_dining(t_data *data, t_philo *philo)
{
	int		i;
	size_t	tmp;

	data->dining_over = 0;
	data->time_start = get_time();
	tmp = ft_current_time(data->time_start);
	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].last_meal_time = tmp;
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].meals_eaten = 0;
		philo[i].finished = 0;
		i++;
	}
}

void	create_process(t_philo *philo, void (*f)(t_philo *), int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i % 2 || (i == n - 1 && n % 2))
			_print(&philo[i], THINK);
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			f(&philo[i]);
			exit(0);
		}
		i++;
	}
}

void	cleanup_the_table(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->died);
	sem_close(data->eat);
	sem_unlink(FORK_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(DIE_SEM);
	sem_unlink(EAT_SEM);
}
