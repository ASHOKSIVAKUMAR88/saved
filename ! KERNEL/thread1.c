#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char message [] = "hellow thread-world";

void * thread_function(void * arg)
{
printf("thread function is running.. Argument was %s\n",(char *) arg);
sleep(3);
strcpy(message,"bye");
pthread_exit("Thanks from pthread function\n");

}


int main() {
int res;
pthread_t thread_id;
void *pthread_result;
res= pthread_create(&thread_id, NULL, thread_function, (void *) message);
if(res!=0) {
	printf("Error creating pthread\n");
	exit(1);
}

printf("main thread, going to wait to finish thread\n");
pthread_join( thread_id,&pthread_result);
if(res!=0) {
	printf("Error pthread_join\n");
	exit(2);
}

printf("pthread_join returned %s\n", (char *)pthread_result);
printf("orignal message: %s\n", message);

}

