/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:39 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/20 17:04:31 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_action_01(t_param *param)
{
	int	i;

	param->eat_time = (int *)malloc(sizeof(int) * param->philo_count);
	if (!param->eat_time)
		return (-1);
	i = 0;
	while (i < param->philo_count)
		param->eat_time[i++] = 0;
	return (0);
}

int	init_param(t_param *param)
{
	int	i;

	if (param->six == 1)
		if (ft_action_01(param))
			return (-1);
	param->last_meal = (int *)malloc(sizeof(int) * param->philo_count);
	param->fork = (int *)malloc(sizeof(int) * param->philo_count);
	if (!param->fork || !param->last_meal)
		return (-1);
	i = 0;
	while (i < param->philo_count)
		param->fork[i++] = 0;
	param->tid = (pthread_t *)malloc(sizeof(pthread_t) * param->philo_count);
	if (!param->tid)
		return (-1);
	param->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
					param->philo_count);
	if (!param->mutex)
		return (-1);
	i = 0;
	while (i < param->philo_count)
		if (pthread_mutex_init(&param->mutex[i++], NULL) != 0)
			return (-1);
	param->is_dead = 1;
	return (0);
}

