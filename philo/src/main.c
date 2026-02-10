/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: louis <louis@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/01/26 20:20:07 by louis			 #+#	#+#			 */
/*   Updated: 2026/01/27 17:08:05 by louis			###   ########.fr	   */
/*																			*/
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

void	parsing(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		printf("philo %d has locked fork %d\n",philo->id, philo->id - 1);
		pthread_mutex_lock(&philo->data->forks[philo->id]);
		printf("philo %d has locked fork %d\n",philo->id, philo->id);
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
	}
	while (1)
	{
		usleep(100);
		if (philo->id == 0)
		{
			pthread_mutex_lock(&philo->data->forks[philo->data->number_of_philosophers]);
			pthread_mutex_lock(&philo->data->forks[philo->id]);
			printf("philo %d has locked fork %d and %d\n",philo->id, philo->id, philo->data->number_of_philosophers);
			pthread_mutex_unlock(&philo->data->forks[philo->data->number_of_philosophers]);
			pthread_mutex_unlock(&philo->data->forks[philo->id]);
			printf("philo %d has unlocked fork %d and %d\n",philo->id, philo->id, philo->data->number_of_philosophers);
		}
		else
		{
			pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
			pthread_mutex_lock(&philo->data->forks[philo->id]);
			printf("philo %d has locked fork %d and %d\n",philo->id, philo->id, philo->id - 1);
			pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
			pthread_mutex_unlock(&philo->data->forks[philo->id]);
			printf("philo %d has unlocked fork %d and %d\n",philo->id, philo->id, philo->id - 1);

		}
	}
		
	return(NULL);
}

t_philo	*init_philo(t_data *data, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->id = id;
	philo->meals_eaten = 0;
	philo->last_meal_time = 0;
	philo->data = data;
	return (philo);
}

int	init_n_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	data->philos = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	i = -1;

	while (++i < data->number_of_philosophers)
	{
		philo = init_philo(data, i);
		if (pthread_create(&data->philos[i], NULL, routine, philo) != 0)
			return (printf("Thread creation failed\n"));
		pthread_mutex_init(&data->forks[i], NULL);
	}
	// pthread_join(data->philos[0], NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			*data;
	// struct timeval	tv;

	if ((ac != 5 && ac != 6) || arg_are_only_digits(av) != 0)
		return (printf("Error, please refer to README to execute\n"));
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	parsing(ac, av, data);
	// gettimeofday(&tv, NULL);
	// printf("%ld\n", tv.tv_sec);
	init_n_philo(data);
	pthread_join(data->philos[data->number_of_philosophers - 1], NULL);
	free(data);
	// printf("test\n");
	return (0);
}
