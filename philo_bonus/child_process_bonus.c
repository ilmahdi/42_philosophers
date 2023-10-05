/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:29:17 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/26 12:45:14 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(t_info *info, size_t time_limit, size_t time_record)
{
	unsigned int	mini_sleep;

	usleep((time_limit - (time_limit * 0.05)) * TO_USEC);
	mini_sleep = 500;
	while ((get_time(info) - time_record) < time_limit)
	{
		usleep(mini_sleep);
		if (mini_sleep > 100)
			mini_sleep /= 2;
	}
}

void	eat_stat(t_info *info)
{
	sem_wait(info->sem_forks);
	print_message(info, TAKE_FORK);
	sem_wait(info->sem_forks);
	print_message(info, TAKE_FORK);
	info->tt_eat_record = get_time(info);
	info->tt_die_record = get_time(info);
	(info->had_eat)++;
	print_message(info, EAT_STAT);
	info->is_eating = 1;
	ft_usleep(info, info->time.tt_eat, info->tt_eat_record);
	sem_post(info->sem_forks);
	sem_post(info->sem_forks);
	info->is_eating = 0;
}

void	*philo_cycle(void *info_ptr)
{
	t_info		*info;

	info = (t_info *)info_ptr;
	if (info->philo_nbr == 1)
		return (print_message(info, THINK_STAT), NULL);
	while (check_sim_over(info) && info->dead_philo != -1)
	{
		if (print_message(info, THINK_STAT))
			break ;
		eat_stat(info);
		info->tt_slp_record = get_time(info);
		if (print_message(info, SLEEP_STAT))
			break ;
		ft_usleep(info, info->time.tt_sleep, info->tt_slp_record);
	}
	return (NULL);
}

void	child_process(t_info *info)
{
	free(info->pid_child);
	if (info->index % 2)
		usleep(100);
	if (pthread_create(&info->philo, NULL, philo_cycle, (void *)info))
		exit(1);
	pthread_detach(info->philo);
	check_dead_stat(info);
	exit(0);
}
