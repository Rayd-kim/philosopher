/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:14:52 by youskim           #+#    #+#             */
/*   Updated: 2022/06/25 21:38:26 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_philo
{
	pthread_t		tid;
	int				num;
	double			life_time;
	int				eat_time;
	int				sleep_time;
	int				eat_num;
	int				left;
	int				right;
	struct s_all	*all;
}		t_philo;

typedef struct s_all
{
	int				philo_num;
	int				eat_num;
	int				life;
	int				death;
	int				eat_check;
	double			start;
	pthread_mutex_t	eating;
	pthread_mutex_t	write;
	pthread_mutex_t	*fork;
	struct s_philo	*philo;
}		t_all;

int				ft_atoi(const char *str);
pthread_mutex_t	*make_fork(t_all *all);
int				make_all(t_all *all, int argc, char *argv[]);
int				make_philo(t_philo *p, int argc, char *argv[], t_all *all);
double			check_time(void);
void			ft_usleep(int spend_time);
void			printf_with_time(double start, int philo, \
				char *str, t_all *all);
int				error_free(t_all *all);
int				error_free_thread(t_all *all, int i);
void			printf_died(double start, int philo, char *str);
int				start_mutex(t_all *all);
void			end_philo(t_all *all);
#endif
