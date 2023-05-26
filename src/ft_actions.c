/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:34 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 20:55:36 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//===========================================================================//
//check life statuse during piking forks                                     //
//===========================================================================//
int	check_dead(t_info *info, t_each each, int rl)
{
	if (info->is_dead == 0 && rl == 0)
	{
		pthread_mutex_unlock(&info->mutex[each.left]);
		info->fork[each.left] = 0;
		return (-1);
	}
	if (info->is_dead == 0 && rl == 1)
	{
		pthread_mutex_unlock(&info->mutex[each.right]);
		info->fork[each.right] = 0;
		return (-1);
	}
	return (0);
}

//===========================================================================//
//take a fork					                                             //
//===========================================================================//
int	take_fork(t_info *info, t_each each)
{
	if (info->fork[each.left] == 0 && info->fork[each.right] == 0)
	{
		if (pthread_mutex_lock(&info->mutex[each.left]) != 0)
			return (-1);
		info->fork[each.left] = 1;
		if (check_dead(info, each, 0) == -1)
			return (-1);
		if (pthread_mutex_lock(&info->mutex[each.right]) != 0)
		{
			pthread_mutex_unlock(&info->mutex[each.left]);
			info->fork[each.left] = 0;
			return (-1);
		}
		info->fork[each.right] = 1;
		if (check_dead(info, each, 1) == -1)
			return (-1);
		printf(YELLOW"%.f ms philo[%d] take a leftfork\n", \
				get_time() - each.start, each.id);
		printf("%.f ms philo[%d] take a rightfork\n"RESET, \
				get_time() - each.start, each.id);
		return (1);
	}
	return (-1);
}

//===========================================================================//
//sleeping action				                                             //
//===========================================================================//
int	ft_sleeping(t_info *info, t_each each)
{
	int	sleep_time;

	sleep_time = info->time_sleep * 1000;
	printf(BLUE"%.f ms philo[%d] is sleeping\n"RESET, \
			get_time() - each.start, each.id);
	if (info->is_dead)
		usleep(sleep_time);
	usleep(2000);
	return (0);
}
