/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:20:24 by louis             #+#    #+#             */
/*   Updated: 2026/02/13 16:29:43 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

// 1 mutex fork + 1 mutex pour le nombre de repas 
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				last_meal_time;
	pthread_mutex_t	meals_mtx;
	pthread_mutex_t fork;
	struct s_data	*data;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_eat;
	t_philo	*head_philo;
	pthread_mutex_t print;
	pthread_mutex_t stop_simulation;
	pthread_t		*philo;
	pthread_t		*check_if_finished;
}	t_data;
// mutex print message philo + soit tu joins thread to main soit mutex dans main 

int		ft_atoi(const char *str);
void	*routine(void *arg);
void	init_node(t_data *data, t_philo *node, int id);
void	init_philo(t_data *data);
void	ft_lstadd_back(t_philo **lst, t_philo *new, int	len);
int		arg_are_only_digits(char **av);
void	safe_print(t_data *data, int i, int meals_eaten);
void	*check_if_finished(void *arg);
void	init_check_if_finished(t_data *data);

#endif