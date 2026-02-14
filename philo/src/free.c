/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:12:25 by marvin            #+#    #+#             */
/*   Updated: 2026/02/14 16:12:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return ;
}

void    free_lst_philo(t_data *data)
{
    t_philo *tmp;
	t_philo *free;
    int i;

    i = -1;
    tmp = data->head_philo;

    while(++i < data->number_of_philos)
	{
		free = tmp;
		pthread_mutex_destroy(&tmp->meals_mtx);
		pthread_mutex_destroy(&tmp->fork);
		tmp = tmp->next;
		ft_free(free);
	}
	return ;
}

void    free_all(t_data *data)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->stop_simulation);
	ft_free(data->philo);
	free_lst_philo(data);
	ft_free(data);
	return ;
}