/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:45 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 20:54:25 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//===========================================================================//
//eat, sleeping, and thinking                                                //
//===========================================================================//
void	ft_life_action(t_info *info, t_each each)
{
	ft_eat(info, each);
	if (info->is_dead)
		ft_sleeping(info, each);
	if (info->is_dead)
		printf("%.f ms philo[%d] is thinking\n", \
				get_time() - each.start, each.id);
}

//===========================================================================//
//the main lifecycle of each philo                                           //
//===========================================================================//
void	*ft_life(void *arg)
{
	t_info	*info;
	t_each	each;
	int		fork;

	info = (t_info *)arg;
	ft_fork_index(info, &each);
	while (info->is_dead)
	{
		each.have_eat = 0;
		if (info->is_dead)
		{
			pthread_mutex_lock(&info->stop);
			fork = take_fork(info, each);
			pthread_mutex_unlock(&info->stop);
			if (fork == 1)
				ft_life_action(info, each);
		}
	}
	return (NULL);
}

//===========================================================================//
//create thread for each philosophers                                        //
//===========================================================================//
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

//===========================================================================//
// initializes the necessary components, creates threads for monitoring and  //
// philosophers, and joins the philosopher threads.                          //
//===========================================================================//
int	philo(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&info->stop, NULL) != 0)
	{
		printf(RED"Failed to initialize mutex\n"RESET);
		return (-1);
	}
	if (pthread_create(&info->m_tid, NULL, ft_check_life, info) != 0)
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

//===========================================================================//
//the main function                                                          //
//===========================================================================//
int	main(int argc, char **argv)
{
	t_info	info;

	info.goal = 0;
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
	if (ft_init_mutex(&info))
		return (1);
	if (philo(&info))
	{
		printf(RED"Error\n"RESET);
		return (1);
	}
	ft_cleanup(&info);
	return (0);
}
