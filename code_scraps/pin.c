#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand((unsigned int)time(NULL));
	
	const int p_count = 6;

	printf("\n PIN: ");
	for(int i=0; i < p_count - 1 ; i++) {
		printf("%d-", rand()%10);
	}
	printf("%d\n", rand()%10);


	return 0;


}
