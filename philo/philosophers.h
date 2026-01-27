/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis <louis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:20:24 by louis             #+#    #+#             */
/*   Updated: 2026/01/27 17:09:00 by louis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal_time;
    pthread_t       thread;
    struct s_data   *data;
} t_philo;

typedef struct s_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int time_to_sleep;
	int  number_of_times_each_philosopher_must_eat;
}	t_data;


int	ft_atoi(const char *str);

#endif