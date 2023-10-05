/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:22:09 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/26 12:34:19 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	i;
	long	res;
	int		s;

	res = 0;
	i = 0;
	s = 1;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (10 * res) + (str[i] - '0');
		i++;
	}
	return (res * s);
}

void	*allocate(size_t size, int len, int init_var)
{
	void	*ptr;

	ptr = malloc(len * size);
	if (!ptr)
		return (NULL);
	memset(ptr, init_var, len * size);
	return (ptr);
}

size_t	get_time(t_info *info)
{
	struct timeval	cur_time;
	size_t			time_ms;

	gettimeofday(&cur_time, NULL);
	time_ms = (cur_time.tv_sec * TO_USEC) + (cur_time.tv_usec / TO_USEC);
	if (!info->time_refrence)
		info->time_refrence = time_ms;
	time_ms -= info->time_refrence;
	return (time_ms);
}

int	print_message(t_info *info, int philo_index, char *msg, int stop_sim)
{
	long		time_ms;
	static int	stop;

	time_ms = get_time(info);
	pthread_mutex_lock(&info->mutex_print_msg);
	if (!stop)
		printf("%ld %d %s\n", time_ms, philo_index, msg);
	else
		return (pthread_mutex_unlock(&info->mutex_print_msg), 1);
	if (stop_sim)
		stop++;
	pthread_mutex_unlock(&info->mutex_print_msg);
	return (0);
}

void	change_tt_die_record(t_info *info, int philo_index)
{
	pthread_mutex_lock(&info->mutex_dead);
	info->tt_die_record[philo_index] = get_time(info);
	pthread_mutex_unlock(&info->mutex_dead);
}
