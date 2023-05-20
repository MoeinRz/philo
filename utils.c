/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:23:00 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/20 13:30:44 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

double get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);

	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int check_eat(t_param *param)
{
	int i;

	i = 0;
	while (i < param->philo_count)
	{
		if (param->eat_time[i++] < param->eat_goal)
			return (-1);
	}
	return (1);
}
