/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:45 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/23 18:19:26 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_last_meal(t_info *param, double init)
{
	int	i;
	int	j;

	i = -1;
	while (++i < param->philo_count)
	{
		param->last_meal[i] += 1;
		if (param->last_meal[i] >= param->time_die)
		{
			param->is_dead = 0;
			printf(RED"%.f ms philo[%d] died\n"RESET, get_time() - init, i + 1);
			j = param->time_die;
			while (j >= 0)
			{
				pthread_mutex_unlock(&param->mutex[j]);
				j--;
			}
			break ;
		}
	}
}

void	*monitoring(void *arg)
{
	t_info	*param;
	double	start;
	double	init;

	param = (t_info *)arg;
	init = get_time();
	usleep(2000 * (param->philo_count - 1));
	while (param->is_dead)
	{
		start = get_time();
		while ((get_time() - start) < 1)
			usleep(1);
		if (param->six == 1 && check_eat(param) == 1)
		{
			param->is_dead = 0;
			break ;
		}
		update_last_meal(param, init);
	}
	return (NULL);
}

int	init_each(t_info *param, t_each *each)
{
	each->id = param->id;
	param->last_meal[each->id - 1] = 0;
	if (each->id == 1)
		each->left = 0;
	else
		each->left = each->id - 1;
	if (each->id == param->philo_count)
		each->right = 0;
	else
		each->right = each->id;
	if (each->left == each->right)
		return (0);
	usleep((param->philo_count + 1 - each->id) * 1000);
	each->start = get_time();
	return (1);
}

void	*my_func(void *arg)
{
	t_info	*param;
	t_each	each;
	int		ret;

	param = (t_info *)arg;
	if (!init_each(param, &each))
	{
		while (param->is_dead)
		{
		}
	}
	else
	{
		while (param->is_dead)
		{
			each.have_eat = 0;
			if (param->is_dead)
			{
				pthread_mutex_lock(&param->stop);
				ret = e_take_fork(param, each);
				pthread_mutex_unlock(&param->stop);
				if (ret == 1)
				{
					eat(param, each);
					if (param->is_dead)
						sleeping(param, each);
					if (param->is_dead)
						printf("%.f ms philo[%d] is thinking\n", get_time() - each.start, each.id);
				}
			}
		}
	}
	return (NULL);
}

int	create_philosophers(t_info *param)
{
	int	i;

	i = 0;
	while (++i <= param->philo_count)
	{
		param->id = i;
		if (pthread_create(&param->tid[i - 1], NULL, my_func, param) != 0)
		{
			printf(RED"Failed to create thread for philosopher %d\n"RESET, i);
			return (-1);
		}
		usleep(1000);
	}
	return (0);
}

int	philo(t_info *param)
{
	int	i;

	if (pthread_mutex_init(&param->stop, NULL) != 0)
	{
		printf(RED"Failed to initialize mutex\n"RESET);
		return (-1);
	}
	if (pthread_create(&param->m_tid, NULL, monitoring, param) != 0)
	{
		printf(RED"Failed to create monitoring thread\n"RESET);
		return (-1);
	}
	pthread_detach(param->m_tid);
	if (create_philosophers(param) != 0)
		return (-1);
	i = 0;
	while (i < param->philo_count)
	{
		if (pthread_join(param->tid[i++], NULL) != 0)
		{
			printf(RED"Failed to join thread for philosopher %d\n"RESET, i);
			return (-1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	param;

	param.six = 0;
	if (argc != 5 && argc != 6)
	{
		printf(RED"Invalid Input\nThe input must be in below format:\n");
		printf("./philosophers [philosopher count] [time to die] ");
		printf("[time to eat] [time to sleep]"RESET"\n");
		return (1);
	}
	if (ft_init(argc, argv, &param))
	{
		printf(RED"Invalid arguments or error\n"RESET);
		return (1);
	}
	if (init_info(&param))
		return (1);
	if (philo(&param))
	{
		printf(RED"Error\n"RESET);
		return (1);
	}
	return (0);
}
