/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:39 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 20:50:21 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//===========================================================================//
//consider eat_time as a counter for goal                                    //
//===========================================================================//
int	ft_action_01(t_info *info)
{
	int	i;

	info->eat_time = (int *)malloc(sizeof(int) * info->philo_count);
	if (!info->eat_time)
		return (-1);
	i = 0;
	while (i < info->philo_count)
		info->eat_time[i++] = 0;
	return (0);
}

//===========================================================================//
//Initialize mutexes and allocate memory for necessary components			 //
//===========================================================================//
int	ft_init_mutex(t_info *info)
{
	int	i;

	if (info->goal == 1)
		if (ft_action_01(info))
			return (-1);
	info->last_meal = (int *)malloc(sizeof(int) * info->philo_count);
	info->fork = (int *)malloc(sizeof(int) * info->philo_count);
	if (!info->fork || !info->last_meal)
		return (-1);
	i = 0;
	while (i < info->philo_count)
		info->fork[i++] = 0;
	info->tid = (pthread_t *)malloc(sizeof(pthread_t) * info->philo_count);
	if (!info->tid)
		return (-1);
	info->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
					info->philo_count);
	if (!info->mutex)
		return (-1);
	i = 0;
	while (i < info->philo_count)
		if (pthread_mutex_init(&info->mutex[i++], NULL) != 0)
			return (-1);
	info->is_dead = 1;
	return (0);
}
