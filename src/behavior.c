/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:34 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/23 23:02:29 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	e_take_fork(t_info *param, t_each each)
{
	if (param->fork[each.left] == 0 && param->fork[each.right] == 0)
	{
		if (pthread_mutex_lock(&param->mutex[each.left]) != 0)
			return (-1);
		param->fork[each.left] = 1;
		if (param->is_dead == 0)
		{
			pthread_mutex_unlock(&param->mutex[each.left]);
			param->fork[each.left] = 0;
			return (-1);
		}
		if (pthread_mutex_lock(&param->mutex[each.right]) != 0)
		{
			pthread_mutex_unlock(&param->mutex[each.left]);
			param->fork[each.left] = 0;
			return (-1);
		}
		param->fork[each.right] = 1;
		if (param->is_dead == 0)
		{
			pthread_mutex_unlock(&param->mutex[each.right]);
			param->fork[each.right] = 0;
			return (-1);
		}
		printf("%.f ms philo[%d] take a leftfork\n", get_time() - each.start, each.id);
		printf("%.f ms philo[%d] take a rightfork\n", get_time() - each.start, each.id);
		return (1);
	}
	return (-1);
}

int	eat(t_info *param, t_each each)
{
	double	start;

	if (param->is_dead == 0)
	{	
		pthread_mutex_unlock(&param->mutex[each.right]);
		pthread_mutex_unlock(&param->mutex[each.left]);
		param->fork[each.right] = 0;
		param->fork[each.left] = 0;
		return (-1);
	}
	printf(GREEN"%.f ms philo[%d] is eating\n"RESET, get_time() - each.start, each.id);
	param->last_meal[each.id - 1] = 0;
	start = get_time();
	while ((get_time() - start) <= param->time_eat)
	{
		if (param->is_dead == 0)
			break ;
		usleep(1000);
	}
	if (each.id % 2 == 0)
	{
		pthread_mutex_unlock(&param->mutex[each.right]);
		pthread_mutex_unlock(&param->mutex[each.left]);
	}
	else
	{
		pthread_mutex_unlock(&param->mutex[each.left]);
		pthread_mutex_unlock(&param->mutex[each.right]);
	}
	param->eat_time[each.id - 1]++;
	param->fork[each.right] = 0;
	param->fork[each.left] = 0;
	return (1);
}

int	sleeping(t_info *param, t_each each)
{
	int	sleep_time;

	sleep_time = param->time_sleep * 1000;
	printf("%.f ms philo[%d] is sleeping\n", get_time() - each.start, each.id);
	if (param->is_dead)
		usleep(sleep_time);
	usleep(2000);
	return (0);
}