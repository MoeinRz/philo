/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:34 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 17:16:27 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	take_fork(t_info *info, t_each each)
{
	if (info->fork[each.left] == 0 && info->fork[each.right] == 0)
	{
		if (pthread_mutex_lock(&info->mutex[each.left]) != 0)
			return (-1);
		info->fork[each.left] = 1;
		if (info->is_dead == 0)
		{
			pthread_mutex_unlock(&info->mutex[each.left]);
			info->fork[each.left] = 0;
			return (-1);
		}
		if (pthread_mutex_lock(&info->mutex[each.right]) != 0)
		{
			pthread_mutex_unlock(&info->mutex[each.left]);
			info->fork[each.left] = 0;
			return (-1);
		}
		info->fork[each.right] = 1;
		if (info->is_dead == 0)
		{
			pthread_mutex_unlock(&info->mutex[each.right]);
			info->fork[each.right] = 0;
			return (-1);
		}
		printf("%.f ms philo[%d] take a leftfork\n", get_time() - each.start, each.id);
		printf("%.f ms philo[%d] take a rightfork\n", get_time() - each.start, each.id);
		return (1);
	}
	return (-1);
}

int	eat(t_info *info, t_each each)
{
	double	start;

	if (info->is_dead == 0)
	{	
		pthread_mutex_unlock(&info->mutex[each.right]);
		pthread_mutex_unlock(&info->mutex[each.left]);
		info->fork[each.right] = 0;
		info->fork[each.left] = 0;
		return (-1);
	}
	printf(GREEN"%.f ms philo[%d] is eating\n"RESET, get_time() - each.start, each.id);
	info->last_meal[each.id - 1] = 0;
	start = get_time();
	while ((get_time() - start) <= info->time_eat)
	{
		if (info->is_dead == 0)
			break ;
		usleep(1000);
	}
	if (each.id % 2 == 0)
	{
		pthread_mutex_unlock(&info->mutex[each.right]);
		pthread_mutex_unlock(&info->mutex[each.left]);
	}
	else
	{
		pthread_mutex_unlock(&info->mutex[each.left]);
		pthread_mutex_unlock(&info->mutex[each.right]);
	}
	info->eat_time[each.id - 1]++;
	info->fork[each.right] = 0;
	info->fork[each.left] = 0;
	return (1);
}

int	sleeping(t_info *info, t_each each)
{
	int	sleep_time;

	sleep_time = info->time_sleep * 1000;
	printf("%.f ms philo[%d] is sleeping\n", get_time() - each.start, each.id);
	if (info->is_dead)
		usleep(sleep_time);
	usleep(2000);
	return (0);
}
