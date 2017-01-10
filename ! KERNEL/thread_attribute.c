#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/*
Control whether the thread is created in the joinable state (value PTHREAD_CREATE_JOINABLE) or in the detached state ( PTHREAD_CREATE_DETACHED).

Default value: PTHREAD_CREATE_JOINABLE.

In the joinable state, another thread can synchronize on the thread termination and recover its termination code using pthread_join(3) . When a joinable thread terminates, some of the thread resources are kept allocated, and released only when another thread performs pthread_join(3) on that thread.

In the detached state, the thread's resources are released immediately when it terminates. pthread_join(3) cannot be used to synchronize on the thread termination.

A thread created in the joinable state can later be put in the detached thread using pthread_detach(3) 
*/

char message [] = "hellow thread-world";
int thread_finished_flag=0;

void * thread_function(void * arg)
{
printf("thread function is running.. Argument was %s\n",(char *) arg);
sleep(3);
strcpy(message,"bye");
thread_finished_flag=1;
pthread_exit("Thanks from pthread function\n");


}


int main() {
int res;
pthread_t thread_id;
void *pthread_result;
pthread_attr_t att;

res = pthread_attr_init(&att);
if(res!=0) {
printf(" error in pthread_attr_init\n");
return 1;
}
res =  pthread_attr_setdetachstate(&att, PTHREAD_CREATE_DETACHED);
if(res!=0) {
	printf("pthread_attr_setdetachstate\n");
	exit(1);
}


res= pthread_create(&thread_id, &att, thread_function, (void *) message);
if(res!=0) {
	printf("Error creating pthread\n");
	exit(1);
}

pthread_attr_destroy(&att);

/*
printf("main thread, going to wait to finish thread\n");
pthread_join( thread_id,&pthread_result);
if(res!=0) {
	printf("Error pthread_join\n");
	exit(2);
}
*/

while(thread_finished_flag == 0)
{
	printf("Main thread waiting\n");
	sleep(1);
}

printf("Message: %s\n", message);

}

