/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:26:11 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/15 10:05:45 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLP "is sleeping"
# define THINK "is thinking"

# define FORK_SEM "/forks"
# define PRINT_SEM "/print"

typedef struct s_data
{
	int				nbr_philo;
	int				eat_limit;
	int				dining_over;
	size_t			time_start;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	sem_t			*forks;
	sem_t			*print;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				finished;
	pid_t			pid;
	size_t			last_meal_time;
	t_data			*data;
}	t_philo;

/*---------input------------*/
int			check_input(char **av);
void		_input(char **av, t_data *data);
void		print_error(char *str);
long long	ft_atoll(const char *str);
size_t		ft_strlen(char *str);

/*---------time-------------*/
size_t		get_time(void);
size_t		ft_current_time(size_t time_start);
int			ft_strcmp(const char *s1, const char *s2);

/*----------dining-----------*/
void		start_dining(t_data *data);
void		_print(t_philo *philo, const char *msg);
int			monitor_philosophers(t_philo *philo);

/*----------dining_utils-----*/
void		init_sema(t_data *data);
void		init_dining(t_data *data, t_philo *philo);
void		create_process(t_philo *philo, void (*f)(t_philo *), int n);
void		cleanup_the_table(t_data *data);

#endif