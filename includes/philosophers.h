/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:22:56 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 21:04:08 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

typedef struct s_each
{
	int		state;
	int		id;
	int		left;
	int		right;
	int		have_eat;
	double	start;
	double	end;
}	t_each;

typedef struct s_info
{
	int				philo_count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				eat_goal;
	int				goal;
	int				id;
	int				is_dead;
	int				count;
	pthread_t		*tid;
	pthread_t		m_tid;
	pthread_mutex_t	stop;
	pthread_mutex_t	*mutex;
	int				*fork;
	int				*last_meal;
	int				*eat_time;
}	t_info;

int		ft_is_pos_digit(char *str);
int		ft_init(int argc, char **argv, t_info *param);
int		ft_isnumber(int a);
int		ft_isspace(char c);
size_t	ft_strlen(char const *str);
int		ft_atoi(const char *str);
int		ft_init_mutex(t_info *param);
void	ft_fork_index(t_info *param, t_each *each);
long	get_time(void);
void	unlok_mutex_fork(t_info *info, t_each each);
int		check_eat(t_info *param);
void	free_fork(t_info *info, t_each each);
int		take_fork(t_info *param, t_each each);
int		o_take_fork(t_info *param, t_each each);
void	update_last_meal(t_info *info, double init);
int		ft_eat(t_info *param, t_each each);
int		ft_sleeping(t_info *param, t_each each);
int		philo(t_info *param);
void	ft_life_action(t_info *info, t_each each);
int		check_dead(t_info *info, t_each each, int rl);
int		create_philosophers(t_info *info);
void	*ft_life(void *arg);
void	*ft_check_life(void *arg);
void	ft_cleanup(t_info *info);
int		philo(t_info *info);

#endif
