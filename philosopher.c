#include "philosopher.h"

int	main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (1);
	//argv[1] 을 atoi로 읽어와서 그 수만큼 philo구조체 만들어서 할당하기.
	//philo 구조체가 포함해야할 정보 : 번호, 수명, 밥 먹는데 소요되는 시간, 잠자는 시간
	//추가로 각 철학자가 최소한 밥을 먹어야하는 횟수 (인자로 안들어올때는 0 이나 -1 로)
	//스레드를 차례대로 실행시키는법 찾아보기
	//뮤텍스로 어떻게 포크를 보호해야하는지 찾아보기
}