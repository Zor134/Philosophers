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

void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (philo->meals_eaten < philo->data->max_eat)
	{
		safe_print(philo->data, philo->id, philo->meals_eaten);
		pthread_mutex_lock(&philo->meals_mtx);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_mtx);
	}
	// while (1)
	// 	;
	sleep(50);
	return(NULL);
}

void	parsing(int ac, char **av, t_data *data)
{
	data->number_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_eat = ft_atoi(av[5]);
	else
		data->max_eat = -1;
	pthread_mutex_init(&data->stop_simulation, NULL);
	pthread_mutex_init(&data->print , NULL);
	init_philo(data);
	pthread_create(&data->check_if_finished, NULL, check_if_finished, data);
	usleep(200);
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

	// int	i = -1;
	// while(++i < data->number_of_philos)
	// {
	// 	pthread_join(*data->head_philo->philo, NULL);
	// 	data->head_philo = data->head_philo->next;
	// }
	printf("test\n");
	pthread_join(data->check_if_finished,NULL);
	free_all(data);
	return (0);
}
