/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:56 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/23 22:51:05 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

typedef struct s_info
{
	int				six;
	int				philo_count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				eat_goal;
	pthread_t		*tid;
	pthread_t		m_tid;
	pthread_mutex_t	stop;
	pthread_mutex_t	*mutex;
	int				*fork;
	int				id;
	int				is_dead;
	int				*last_meal;
	int				*eat_time;
}	t_info;

typedef struct s_each
{
	int		id;
	int		left;
	int		right;
	int		have_eat;
	double	start;
	double	end;
}	t_each;

int		ft_init(int argc, char **argv, t_info *param);
size_t	ft_strlen(char const *str);
int		ft_atoi(const char *str);
int		init_info(t_info *param);
int		init_each(t_info *param, t_each *each);
long	get_time(void);
int		check_eat(t_info *param);
int		e_take_fork(t_info *param, t_each each);
int		o_take_fork(t_info *param, t_each each);
int		eat(t_info *param, t_each each);
int		sleeping(t_info *param, t_each each);
int		philo(t_info *param);
void	*my_func(void *arg);
void	*monitoring(void *arg);

#endif
