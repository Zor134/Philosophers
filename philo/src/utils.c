/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:53:58 by laudinot          #+#    #+#             */
/*   Updated: 2026/02/14 16:18:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	arg_are_only_digits(char **av)
{
	int	i;
	int	y;

	i = 0;
	while (av[++i])
	{
		y = -1;
		while (av[i][++y])
		{
			if ((av[i][y] < '0' || av[i][y] > '9') && av[i][y] != '+')
				return (printf
					("Please enter NUMERIC and POSITIVE arguments only.\n"));
		}
	}
	return (0);
}

void	safe_print(t_data *data, int i, int meals_eaten)
{
	pthread_mutex_lock(&data->print);
	printf("Philo n%d has eaten meal number %d\n", i, meals_eaten);
	pthread_mutex_unlock(&data->print);
	// if (i == data->number_of_philos)
	// 	pthread_mutex_unlock(data->stop_simulation);

}

void	*check_if_finished(void *arg)
{
	int	count;
	t_philo *tmp;
	t_data *data;

	data = arg;
	tmp = data->head_philo;
	count = 0;
	pthread_mutex_lock(&data->stop_simulation);
	while (count < data->number_of_philos)
	{
		pthread_mutex_lock(&tmp->meals_mtx);
		if (tmp->meals_eaten == data->max_eat)
		{
			tmp->meals_eaten++;
			count++;
		}
		pthread_mutex_unlock(&tmp->meals_mtx);
		tmp = tmp->next;
	}
	pthread_mutex_unlock(&data->stop_simulation);
	return (NULL);
}