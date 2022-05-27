#include "philosopher.h"

typedef struct	s_list
{
	char	*p;
	int		*k;
	int		num;
	pthread_mutex_t	*mutex;
}		t_list;


typedef struct	s_thread
{
	struct s_list	*list;
}		t_thread;

void	*t_funtion(void *data)
{
	pthread_t	tid;

	tid = pthread_self();
	t_list	*list;
	list = (t_list *)data;
	printf("%d\n", pthread_mutex_lock(list->mutex));
	for (int i = 1; i < 6; i++)
	{
		list->k[list->num] += 1;
		printf ("[%s] --- %d\n", list->p, list->k[list->num]);
		usleep(1000*1000);
		printf ("1 더해짐\n");
	}
	pthread_mutex_unlock(list->mutex);
	return (0);
}

int main(void)
{
    pthread_t	a[2];
    int			thr_id;
	int			status;

	pthread_mutex_t	mutex;
	
	//pthread_mutex_init(&mutex, NULL);
	char	*p[2];
	p[0] = "thread_1";
	p[1] = "thread_2";
	int		b[2] = {0, 0};

	t_thread	*thread = malloc(sizeof(t_thread) * 2);
	thread[0].list = (t_list *)malloc(sizeof(t_list));
	thread[1].list = (t_list *)malloc(sizeof(t_list));

	for (int i = 0; i < 2; i++)
	{
		thread[i].list->num = i;
		thread[i].list->p = p[i];
		thread[i].list->k = b;
		thread[i].list->mutex = &mutex;
	}
	pthread_mutex_init(thread[0].list->mutex, NULL);
	
	for (int i = 0; i < 2; i++)
	{
		thr_id = pthread_create(&a[i], NULL, t_funtion, (void *)thread[i].list);
		//usleep(1000 * 1000);
	}
	
	pthread_join(a[0], (void **)&status);
	pthread_join(a[1], (void **)&status);
	printf("program_end\n");
	return 0;
}
