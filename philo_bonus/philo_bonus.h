/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:29:58 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/26 12:32:54 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

# define TO_USEC 1000

# define TAKE_FORK "has taken a fork"
# define THINK_STAT "is thinking"
# define SLEEP_STAT "is sleeping"
# define EAT_STAT "is eating"
# define DEAD_STAT "died"

typedef struct s_times
{
	int		sim_over_nbr;
	size_t	tt_die;
	size_t	tt_eat;
	size_t	tt_sleep;
}	t_times;

typedef struct s_info
{
	bool			is_eating;
	unsigned int	index;
	unsigned int	had_eat;
	size_t			tt_die_record;
	size_t			tt_eat_record;
	size_t			tt_slp_record;
	pthread_t		philo;
	pid_t			*pid_child;
	char			dead_philo;
	unsigned int	philo_nbr;
	size_t			time_refrence;
	t_times			time;
	sem_t			*sem_forks;
	sem_t			*sem_print_msg;
}	t_info;

size_t	get_time(t_info *info);
int		ft_atoi(const char *str);
void	child_process(t_info *info);
int		print_message(t_info *info, char *msg);
void	check_dead_stat(t_info *info);
int		check_sim_over(t_info *info);
void	kill_process(t_info *info);

#endif
