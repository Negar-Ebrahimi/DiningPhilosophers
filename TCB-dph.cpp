#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var=PTHREAD_COND_INITIALIZER;
int chopstick[6]={1,1,1,1,1,1};


class TCB {
	public:
	int philosopherNumber;
	TCB(int th_id) {
		philosopherNumber = th_id;
        thinking();
        printf("The philosopher %d is gonna eat for a while.\n", philosopherNumber);
        pickup_forks();
		return_forks();
	}

	void thinking(){
	int duration=(rand()%3)+1;
	printf("The philosopher %d is gonna think for a while.\n", philosopherNumber);
	sleep(duration);
	}

	void pickup_forks(){ //The philosopher wishes to eat
	pthread_mutex_lock(&mutex);
	while (chopstick[philosopherNumber]==0 || chopstick[(philosopherNumber+1)%5]==0){
		pthread_cond_wait(&cond_var, &mutex);
	}
	chopstick[philosopherNumber]=0;
	chopstick[(philosopherNumber+1)%5]=0;
	printf("The philosopher %d picked up both of the chopsticks.\n", philosopherNumber);
	sleep((rand()%3)+1);
	pthread_mutex_unlock(&mutex);
	}

	void return_forks(){ //The philosopher has finished eating
	pthread_mutex_lock(&mutex);
	chopstick[philosopherNumber]=1;
	chopstick[(philosopherNumber+1)%5]=1;
	pthread_cond_signal(&cond_var);
	printf("The philosopher %d returned both of the chopsticks.\n", philosopherNumber);
	pthread_mutex_unlock(&mutex);
	}


};

int main(){
	srand(time(NULL));
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond_var,NULL);

	TCB *philosopher1=new TCB(1);
	TCB *philosopher2=new TCB(2);
	TCB *philosopher3=new TCB(3);
	TCB *philosopher4=new TCB(4);
	TCB *philosopher5=new TCB(5);



	return 0;
}
