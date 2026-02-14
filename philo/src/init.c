/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:55:08 by laudinot          #+#    #+#             */
/*   Updated: 2026/02/14 16:28:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	init_node(t_data *data, t_philo *node, int id)
{
	node->id = id;
	node->meals_eaten = 0;
	node->last_meal_time = 0;
	pthread_mutex_init(&node->meals_mtx, NULL);
	pthread_mutex_init(&node->fork, NULL);
	node->data = data;
	node->next = NULL;
}

void	create_thread(t_data *data)
{
	int i;
	t_philo *tmp;
	
	tmp = data->head_philo;
	i = -1;
	data->philo = malloc(data->number_of_philos * sizeof(pthread_t));
	if (!data->philo)
		return;
	while (++i < data->number_of_philos)
	{
		if (i % 2 == 0)
		{
			pthread_create(&data->philo[i], NULL, routine, tmp);
			usleep(50);
		}
		tmp = tmp->next;
	}
	usleep(500);
	tmp = data->head_philo;
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (i % 2 == 1)
		{
			pthread_create(&data->philo[i], NULL, routine, tmp);
			usleep(50);
		}
		tmp = tmp->next;
	}

}

void	init_philo(t_data *data)
{
	int	i;
	t_philo *tmp;
	i = -1;
	data->head_philo = malloc(sizeof(t_philo) * data->number_of_philos);
	while (++i < data->number_of_philos)
	{
		tmp = malloc(sizeof(t_philo));
		if (!tmp)
			return;
		init_node(data, tmp, i);
		ft_lstadd_back(&data->head_philo, tmp, data->number_of_philos);
	}
	create_thread(data);
}
