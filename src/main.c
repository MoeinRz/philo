/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:45 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 12:47:20 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_last_meal(t_info *info, double init)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->philo_count)
	{
		info->last_meal[i] += 1;
		if (info->last_meal[i] >= info->time_die)
		{
			info->is_dead = 0;
			printf(RED"%.f ms philo[%d] died\n"RESET, get_time() - init, i + 1);
			j = info->time_die;
			while (j >= 0)
			{
				pthread_mutex_unlock(&info->mutex[j]);
				j--;
			}
			break ;
		}
	}
}

void	*monitoring(void *arg)
{
	t_info	*info;
	double	start;
	double	init;

	info = (t_info *)arg;
	init = get_time();
	usleep(2000 * (info->philo_count - 1));
	while (info->is_dead)
	{
		start = get_time();
		while ((get_time() - start) < 1)
			usleep(1);
		if (info->six == 1 && check_eat(info) == 1)
		{
			info->is_dead = 0;
			break ;
		}
		update_last_meal(info, init);
	}
	return (NULL);
}

int	init_each(t_info *info, t_each *each)
{
	pthread_mutex_lock(&info->stop);
	each->id = info->id;
	info->last_meal[each->id - 1] = 0;
	if (each->id == 1)
		each->left = 0;
	else
		each->left = each->id - 1;
	if (each->id == info->philo_count)
		each->right = 0;
	else
		each->right = each->id;
	if (each->left == each->right)
	{
		pthread_mutex_unlock(&info->stop);
		return (0);
	}
	each->start = get_time();
	pthread_mutex_unlock(&info->stop);
	usleep((info->philo_count - each->id + 1) * 1000);
	return (1);
}

void	*ft_life(void *arg)
{
	t_info	*info;
	t_each	each;
	int		ret;

	info = (t_info *)arg;
	if (!init_each(info, &each))
	{
		while (info->is_dead)
		{
		}
	}
	else
	{
		while (info->is_dead)
		{
			each.have_eat = 0;
			if (info->is_dead)
			{
				pthread_mutex_lock(&info->stop);
				ret = e_take_fork(info, each);
				pthread_mutex_unlock(&info->stop);
				if (ret == 1)
				{
					eat(info, each);
					if (info->is_dead)
						sleeping(info, each);
					if (info->is_dead)
						printf("%.f ms philo[%d] is thinking\n", get_time() - each.start, each.id);
				}
			}
		}
	}
	return (NULL);
}


int	create_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (++i <= info->philo_count)
	{
		info->id = i;
		if (pthread_create(&info->tid[i - 1], NULL, ft_life, info) != 0)
		{
			printf(RED"Failed to create thread for philosopher %d\n"RESET, i);
			return (-1);
		}
		usleep(1000);
	}
	return (0);
}

int	philo(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&info->stop, NULL) != 0)
	{
		printf(RED"Failed to initialize mutex\n"RESET);
		return (-1);
	}
	if (pthread_create(&info->m_tid, NULL, monitoring, info) != 0)
	{
		printf(RED"Failed to create monitoring thread\n"RESET);
		return (-1);
	}
	pthread_detach(info->m_tid);
	if (create_philosophers(info) != 0)
		return (-1);
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_join(info->tid[i++], NULL) != 0)
		{
			printf(RED"Failed to join thread for philosopher %d\n"RESET, i);
			return (-1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	info.six = 0;
	if (argc != 5 && argc != 6)
	{
		printf(RED"Invalid Input\nThe input must be in below format:\n");
		printf("./philosophers [philosopher count] [time to die] ");
		printf("[time to eat] [time to sleep]"RESET"\n");
		return (1);
	}
	if (ft_init(argc, argv, &info))
	{
		printf(RED"Invalid arguments or error\n"RESET);
		return (1);
	}
	if (init_mutex(&info))
		return (1);

	if (philo(&info))
	{
		printf(RED"Error\n"RESET);
		return (1);
	}
	return (0);
}
