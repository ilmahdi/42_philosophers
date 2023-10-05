/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:20:38 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/26 12:23:36 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_sim_over(t_info *info)
{
	int	i;

	i = -1;
	if (info->time.sim_over_nbr == -1)
		return (1);
	while ((unsigned int)++i < info->philo_nbr)
	{
		if (info->had_eat[i] < (unsigned int)info->time.sim_over_nbr)
			return (1);
	}
	info->dead_philo = -1;
	return (0);
}

void	check_dead_stat(t_info *info)
{
	int	i;

	while (info->dead_philo != -1)
	{
		i = -1;
		while ((unsigned int)++i < info->philo_nbr && !usleep(1000))
		{
			pthread_mutex_lock(&info->mutex_is_eating);
			if (info->is_eating[i])
			{
				pthread_mutex_unlock(&info->mutex_is_eating);
				continue ;
			}
			pthread_mutex_lock(&info->mutex_dead);
			pthread_mutex_unlock(&info->mutex_is_eating);
			if ((get_time(info) - info->tt_die_record[i]) > info->time.tt_die)
			{
				info->dead_philo = -1;
				pthread_mutex_unlock(&info->mutex_dead);
				print_message(info, i + 1, DEAD_STAT, 1);
				break ;
			}
			pthread_mutex_unlock(&info->mutex_dead);
		}
	}
}
