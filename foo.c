#include <pthread.h>

void *paramFunc(void *arg0);

int main(int argc, char** argv) {

	pthread_t thread0, thread1;
	char *msg0 = "thread0";
	char *msg1 = "thread1";

	int return0, return1;

	return0 = pthread_create(&thread0, NULL, paramFunc, (void *) msg0);
	return1 = pthread_create(&thread1, NULL, paramFunc, (void *) msg1);

	return 0;
}
void *paramFunc(void *arg1) {
		char *msg;
		msg = (char *)arg1;

		int i;
		for (i=0;i<15;i++) {
			printf("%s %d\n",msg, i );

		}
		return NULL;
	}
