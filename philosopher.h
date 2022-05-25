#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_philo
{
	pthread_t	tid;
	int			num;
	int			life;
	int			eat_time;
	int			sleep_time;
	int			eat_num;
}		t_philo;

typedef struct s_all
{
	int				num;
	pthread_mutex_t	*pork;
	struct s_philo	*philo;
}		t_all;

int	ft_atoi(const char *str);

#endif