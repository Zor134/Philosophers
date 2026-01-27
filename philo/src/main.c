/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis <louis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:20:07 by louis             #+#    #+#             */
/*   Updated: 2026/01/27 17:08:05 by louis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int     arg_are_only_digits(char **av)
{
    int i;
    int y;

    i = 0;
    while (av[++i])
    {
        y = -1;
        while(av[i][++y])
        {
            if ((av[i][y] <= '0' || av[i][y] >= '9') && av[i][y] != '+')
                return(printf("Please enter NUMERIC and POSITIVE arguments only.\n"));
        }
    }
    return (0);
}

void    parsing(int ac, char **av, t_data *data)
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

int main(int ac, char **av)
{
    if ((ac != 5 && ac != 6 )|| arg_are_only_digits(av) != 0)
        return (printf("How to execute : ./Philo <number_of_philosophers> <time_to_die> <time_to_eat time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"));
    t_data *data;

    data = malloc(sizeof(t_data));
    if (data == NULL)
        return (1);
    parsing(ac, av, data);
    // printf("number_of_philosophers = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\nmust_eat = %d\n", data->number_of_philosophers, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->number_of_times_each_philosopher_must_eat);
    
    free(data);
    return(0);
}