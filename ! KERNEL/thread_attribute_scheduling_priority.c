#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int thread_finished_flag = 0;
int start=0;
int high_priority_loop_count = 0;
int low_priority_loop_count =0;

void * high_priority_thread_function(void * arg)
{
	while(start!=1);
	
	while(1)
	{
		high_priority_loop_count++;
		usleep(1);
	}

}

void * low_priority_thread_function(void * arg)
{
	while(start!=1);
	while(1)
	{
		low_priority_loop_count++;
		usleep(1);
	}
}



int main() {
int res;

int min;
int max;
struct sched_param schedule_parameter;

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

res =  pthread_attr_setschedpolicy(&att, SCHED_OTHER);
if(res!=0) {
	printf("pthread_attr_setdetachstate\n");
	exit(1);
}

min = sched_get_priority_min(SCHED_OTHER);
max = sched_get_priority_max(SCHED_OTHER);
memset(&schedule_parameter,0,sizeof(schedule_parameter));
schedule_parameter.sched_priority = min;
pthread_attr_setschedparam(&att, &schedule_parameter);

res= pthread_create(&thread_id, &att, low_priority_thread_function, (void *) NULL);
if(res!=0) {
	printf("Error creating pthread\n");
	exit(1);
}

schedule_parameter.sched_priority = max;
pthread_attr_setschedparam(&att, &schedule_parameter);

res= pthread_create(&thread_id, &att, high_priority_thread_function, (void *) NULL);
if(res!=0) {
	printf("Error creating pthread\n");
	exit(1);
}


pthread_attr_destroy(&att);

start =1;
sleep(3);
printf("High Pririty thread loop count: %d\n", high_priority_loop_count);
printf("Low Pririty thread loop count: %d\n",  low_priority_loop_count);


}

