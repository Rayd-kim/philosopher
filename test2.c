#include "philosopher.h"

void	*t_funtion(void *data)
{
	pthread_t	tid;

	tid = pthread_self();
	(t_list)list = (t_list)data;
	printf ("[%s] tid: %x --- %d\n", thread_name, (unsigned int)tid, 0);
	
	return (0);
}

typedef struct	s_list
{
	char	*p;
	int		*k;
}		t_list;

int main(void)
{
    pthread_t	a[2];
    int			thr_id;
	int			status;

	pthread_mutex_t	pork[2];
	
	char	p[2];
	p[0] = "thread_1";
	p[1] = "thread_2";
	int		b[2] = {0, };

	t_list	list;
	list.p = p;
	list.k = b;

	thr_id = pthread_create(&a[0], NULL, t_funtion, (void *)list);
	thr_id = pthread_create(&a[1], NULL, t_funtion, (void *)list);

	
	pthread_join(a[0], (void **)&status);
	pthread_join(a[1], (void **)&status);
	printf("program_end\n");
	return 0;
}
https://reakwon.tistory.com/98